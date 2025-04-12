// Learn how to make ImMobile scripts at:
// https://github.com/basharast/ImMobile/wiki/DevJSRuntime

// BingWallpapers script by Bashar Astifan
// Doing the same in Extension is far less efforts than below

imm.resetRuntime(); // Ensure a clean runtime at start

// Utility: Copy file using raw ArrayBuffer
function copyFile(sourcePath, destinationPath) {
	const { open, close, read, write, O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC } = imm.os;
	const BUFFER_SIZE = 1024;
	const rawBuffer = new ArrayBuffer(BUFFER_SIZE);

	const sourceFd = open(sourcePath, O_RDONLY);
	if (sourceFd < 0) throw new Error(`Failed to open source file: ${sourcePath}`);

	const destFd = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC);
	if (destFd < 0) {
		close(sourceFd);
		throw new Error(`Failed to open/create destination file: ${destinationPath}`);
	}

	try {
		let bytesRead;
		while ((bytesRead = read(sourceFd, rawBuffer, 0, BUFFER_SIZE)) > 0) {
			write(destFd, rawBuffer, 0, bytesRead);
		}
	} finally {
		close(sourceFd);
		close(destFd);
	}

	console.log('File copied successfully.');
}

// Utility: Extract file name from Bing image URL
function getFileName(fileURL) {
	let fileName = "wallpaper.jpg";
	try {
		const match = fileURL.match(/id=([^&]+)/);
		if (match && match[1]) {
			fileName = match[1];
		} else {
			console.log("No filename match found.");
		}
	} catch (e) {
		console.error("Filename extraction error:", e);
	}

	console.log("Filename:", fileName);
	return fileName;
}

// Main logic: Fetch, download, and set Bing wallpaper
async function FetchBingWallpaper() {
	if (!imm.isOnline()) return;

	// Fetch Bing image metadata
	const response = imm.getResponse('https://www.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1');
	const data = JSON.parse(response);
	const imageInfo = data.images[0];
	const baseUrl = "https://www.bing.com";

	// Get image URLs (both portrait and landscape)
	const wallpaperLandscape = `${baseUrl}${imageInfo.url}`;
	const wallpaperVertical = wallpaperLandscape.replace(/(\d+)x(\d+)/, '1080x1920');
	const wallpaperInfo = imageInfo.copyright;

	console.warn(`Landscape: ${wallpaperLandscape}`);
	console.warn(`Info: ${wallpaperInfo}`);

	// Prepare folder paths and image filename
	const downloadsFolder = "$downloads";
	const bingWallpapers = "BingWallpapers";
	const imageFilename = getFileName(wallpaperLandscape);
	const folderPath = imm.createFolder(downloadsFolder, bingWallpapers);

	if (!folderPath) {
		console.error("Failed to create wallpapers folder");
		return;
	}

	const wallpaperPath = `${folderPath}\\${imageFilename}`;
	console.success(`Wallpaper target path: ${wallpaperPath}`);

	// Download and apply wallpaper if it doesn't exist
	imm.quickDownload(wallpaperVertical, `${bingWallpapers}\\${imageFilename}`);

	console.warn(`Applying background: ${imageFilename}`);
	imm.changeBackground(wallpaperPath);

	// Delay + Notify
	await imm.sleepAsync(4000);
	imm.notify(wallpaperInfo, "info");
}

// Kick off the process
FetchBingWallpaper();
