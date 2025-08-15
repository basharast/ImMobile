/*
Date: 2025-Present

Bashar Astifan (https://github.com/basharast):
ImMobile Extension
Legacy support as tested on 8.1 (6.3.9651.0)
*/

#pragma once

#include "pch.h"
#include "IExtension.h"

std::string GetFileName(const std::string& fileURL) {
	std::string fileName = "wallpaper.jpg";

	try {
		std::regex pattern(R"(id=([^&]+))");
		std::smatch match;

		if (std::regex_search(fileURL, match, pattern) && match.size() > 1) {
			fileName = match[1].str();
		}
		else {
			Imm::Logger::Normal("No filename match found.");
		}
	}
	catch (const std::exception& e) {
		Imm::Logger::Normal("Filename extraction error: " + std::string(e.what()));
	}

	Imm::Logger::Normal("Filename: " + fileName);
	return fileName;
}

void FetchBingWallpaper() {
	// Check if the device is currently online
	if (Imm::Online::IsOnline()) {

		// Fetch JSON metadata from Bing's wallpaper API
		std::string reponse = Imm::Online::GetResponse("https://www.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1");
		// Parse the JSON using picojson
		picojson::value root;
		std::string err = picojson::parse(root, reponse);
		if (!err.empty()) {
			throw std::runtime_error("JSON parse error: " + err);
		}

		// Check if the root object is valid and has "images"
		if (!root.is<picojson::object>()) {
			throw std::runtime_error("Expected JSON object at root.");
		}

		auto& obj = root.get<picojson::object>();
		auto imagesIt = obj.find("images");
		if (imagesIt == obj.end() || !imagesIt->second.is<picojson::array>()) {
			throw std::runtime_error("Missing or invalid 'images' array.");
		}

		const picojson::array& images = imagesIt->second.get<picojson::array>();
		if (images.empty() || !images[0].is<picojson::object>()) {
			throw std::runtime_error("Invalid image info.");
		}

		const picojson::object& imageInfo = images[0].get<picojson::object>();

		// Construct full image URL
		std::string baseUrl = "https://www.bing.com";
		std::string wallpaperLandscape = baseUrl + imageInfo.at("url").get<std::string>();

		// Generate portrait version by replacing resolution in URL
		std::string wallpaperVertical = std::regex_replace(wallpaperLandscape, std::regex(R"((\d+)x(\d+))"), "1080x1920");

		// Extract copyright
		std::string wallpaperInfo = imageInfo.at("copyright").get<std::string>();

		// Log the resolved URLs and metadata
		Imm::Logger::Warn("Landscape: " + wallpaperLandscape);
		Imm::Logger::Warn("Info: " + wallpaperInfo);

		// Prepare target folders for storing wallpapers
		std::string picturesFolder = Imm::Storage::Locations::PicturesFolder() + "\\BingWallpapers";
		std::string picturesLandscapeFolder = picturesFolder + "\\landscape";
		Imm::Storage::Manage::CreateFolder(picturesFolder, false, true);
		Imm::Storage::Manage::CreateFolder(picturesLandscapeFolder, false, true);

		// Get a clean file name from the wallpaper URL
		std::string imageFilename = GetFileName(wallpaperLandscape);

		// Define full paths for saving the images
		std::string wallpaperPath = picturesFolder + "\\" + imageFilename;
		std::string wallpaperLandscapePath = picturesLandscapeFolder + "\\" + imageFilename;

		// Log target path
		Imm::Logger::Warn("Wallpaper path: " + wallpaperPath);

		// Only download if the image doesn't already exist
		if (!Imm::Storage::Manage::IsExists(wallpaperPath)) {

			// Attempt to download the portrait version first
			if (Imm::Online::QuickDownload(wallpaperVertical, wallpaperPath, true, Imm::Online::GetDefaultDownloadClient(), false)) {

				// Then download the landscape version to a separate folder
				if (Imm::Online::QuickDownload(wallpaperLandscape, wallpaperLandscapePath, true, Imm::Online::GetDefaultDownloadClient(), false)) {

					// Copy the landscape image to app's internal backgrounds folder
					std::string backgroundLandscapeFolder = Imm::Storage::Locations::DataFolder() + "\\backgrounds\\landscape";
					std::string destImage = backgroundLandscapeFolder + "\\background.jpg";

					Imm::Logger::Warn("Copy wallpaper to: " + destImage);
					Imm::Storage::Manage::Copy(wallpaperLandscapePath, destImage);
				}
				else {
					// Log failure if landscape download fails
					Imm::Logger::Error("Failed to download: " + wallpaperLandscape);
				}

				// Apply the portrait wallpaper as the current background
				Imm::App::UI::CustomBackground(wallpaperPath);
			}
			else {
				// Log failure if portrait download fails
				Imm::Logger::Error("Failed to download: " + wallpaperVertical);
			}
		}
		else {
			// Skip download and notify success if file already exists
			Imm::Logger::Success("Wallpaper already exists and set: " + imageFilename);
		}

		// Notify user with wallpaper info after a short delay
		concurrency::create_task([wallpaperInfo] {
			Sleep(3000);
			Imm::Notify::Info(wallpaperInfo, 6000);
			Imm::Logger::Notice(wallpaperInfo);
		});
	}
}
