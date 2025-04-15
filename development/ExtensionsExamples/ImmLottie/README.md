## ImLottie Extension

Extension based on [imlottie](https://github.com/dalerank/imlottie) by [dalerank](https://github.com/dalerank)


## Important

Don't use this as base template, instead refer to the main template

Refer to the [Wiki page](https://github.com/basharast/ImMobile/wiki/DevExtensions) for 🔌 Extensions development

## Remarks
The only change I made is to use ImmApi provider to load the file instead of the fopen

at `imottie_renderer.cpp`, [Line](https://github.com/basharast/ImMobile/blob/7de44d60a4673581d07947c76dcbeb6055982d00/development/ExtensionsExamples/ImmLottie/Core/imottie_renderer.cpp#L5939)

```cpp
bool LottieLoader::load(const std::string &path, bool cachePolicy)
{
  //...
  // Read contents
  bool state = false;
  std::string content= Imm::Storage::Stream::FileGetContents(state, path, "r");
  if (!state) {
    return { };
  }
  //...
}
```

also at the main extension code I ensured that all cleaned up for correct unload

at `ImmLottie.cpp`, [Line](https://github.com/basharast/ImMobile/blob/7de44d60a4673581d07947c76dcbeb6055982d00/development/ExtensionsExamples/ImmLottie/ImmLottie.cpp#L281)

```cpp
void Unloading() override {
  // ImMobile is unloading the extension
  // cleanup your stuff to avoid failing
  ImLottie::destroy();
}
```

## Libraries

- [FreeType](https://github.com/freetype) 
- [stb_image](https://github.com/nothings/stb)

