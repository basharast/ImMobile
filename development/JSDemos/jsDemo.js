/**
 * @author Bashar Astifan
 * @copyright 2025
 * @description ImMobile JSRuntime Extension
 */

/*******************/
/* Reset JSRuntime */
/*******************/
imm.resetRuntime();

/********************/
/* JSRuntime Render */
/********************/
// Render is not supported for now (future usage)
function render(visible) {
    // [BEGIN | DON'T REMOVE]
    if (imm.WindowBegin()) {

        /* [DRAW YOUR CONTENT HERE] */

    }
    else {
        // Window is not active
    }

    // [END  | DON'T REMOVE]
    imm.WindowEnd();
}

/**************/
/* Tests Area */
/**************/
// Manual delay
function delay(milliseconds) {
    return new Promise(resolve => {
        const start = Date.now();
        while (Date.now() - start < milliseconds) {
            // Busy-waiting loop to simulate a delay
        }
        resolve();
    });
}

// File picker callback
function fileCallback(path) {
    imm.notify("File: " + path, "success");
    if (path.indexOf(".zip") !== -1) {
        imm.unZip(path, "$exts");
    } else {
        imm.openFile(path);
    }
}

// Folder picker call back
function folderCallback(path) {
    imm.notify("Folder: " + path, "success");
    imm.zipFolder(path, "$exts/folder.zip");
}

// Save picker callback
function saveCallback(path) {
    imm.notify("Folder: " + path, "success");
    var targetURL = "https://jsonplaceholder.typicode.com/todos/1";
    console.warn("Response: " + targetURL);
    var response = imm.getResponse(targetURL);
    console.error(response);
    console.log(JSON.parse(response).title);
    imm.filePutContents(path, response);
}

function gitHubCallback(output) {
    console.warn(output);
}

// Download file test
function testFileDownload() {
    var testURL = "https://github.com/basharast/wut/releases/download/1.5.0/WUTMini.1.5.0_ARM.7z";
    var filename = imm.getOnlineFileName(testURL, "test.7z");
    console.warn(filename);
    imm.quickDownload(testURL, filename);
}

// Confirm dialog callback
function confirmDialogCallback(state) {
    if (state) {
        console.warn("User confirmed");
    } else {
        console.error("User rejected");
    }
}

// Input dialog callback
function inputDialogCallback(state, input) {
    if (state) {
        console.warn("User confirmed, input: " + input);
    } else {
        console.error("User cancelled");
    }
}

// Check extension state
function extState(path) {
    var state = imm.isExtenLoaded(path);
    console.warn("Extension state: " + (state ? "loaded" : "not loaded"));

    return state;
}

// Load ImExtension
function loadExt() {
    var demoExt = "$exts/ImmExtenTemplate.dll";
    if (!extState(demoExt)) {
        imm.loadExten(demoExt, false, false);
        if (extState(demoExt)) {
            imm.notify("Extension loaded", "success");
        }
    } else {
        imm.notify("Extension already loaded", "warn");
    }
}

// Show extension GUI
function extenGUI() {
    var demoExt = "$exts/ImmExtenTemplate.dll";
    if (extState(demoExt)) {
        imm.extenToggleGUI();
    } else {
        imm.notify("Extension not loaded", "error");
    }
}

// Show github readme
function showReadMe() {
    var repoURL = "https://github.com/basharast/RetroArch-ARM";
    imm.showGitHubReadMeUI(repoURL);
}

// Random string
function generateRandomString(length) {
    const characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    const charactersLength = characters.length;

    let result = '';
    for (let i = 0; i < length; i++) {
        const randomIndex = Math.floor(Math.random() * charactersLength);
        result += characters[randomIndex];
    }
    return result;
}

// Test function
async function startTest() {
    const now = new Date();
    imm.notify("Timer started", "warn");
    await imm.sleepAsync(2500);
    var timeString = now.toLocaleTimeString();
    console.error(timeString);
    imm.notify("Time now is: " + timeString, "success");

    console.warn(Math.floor(3.14944));
    console.error("test hello man".indexOf("hello"));

    await imm.sleepAsync(1000);
    //imm.toast("ImMobile JS","Script finished");

    //imm.showKeyboard(true);
    //await imm.sleepAsync(2000);
    //imm.showKeyboard(false);

    //imm.chooseFile(fileCallback);
    //imm.chooseFolder(folderCallback);
    //imm.saveFile(saveCallback);

    if (imm.isOnline()) {
        console.warn("Online");
    } else {
        console.error("Offline");
    }

    //console.warn("Clipboard: " + getClipboard());

    //imm.gitHubContent("basharast", "make-uwp", gitHubCallback);
    //imm.gitHubLatestRelease("basharast", "A2IPrompt", gitHubCallback);

    //testFileDownload();

    //imm.confirmDialog("Test Confirm", "Confirm dialog JS test", confirmDialogCallback);
    //imm.inputDialog("Test Input", "Enter your name", inputDialogCallback);

    //imm.std.gc();
}

// Update time immediately and then every second
console.success("JSRuntime (index-> $jsIndex, id-> $jsID, time-> $jsTime)");

// Random string test
console.warn("Random String: " + generateRandomString(10));

// Start test timer
imm.notify("JSRuntime ($jsID) started");
imm.setTimeout(startTest, 2500);
