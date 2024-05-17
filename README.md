# DESCRIPTION
ELIZA chatbot wrapped into a GDExtension, if you want to use it in your game :)

# BUILDING
Clone godot-cpp bindings into the subdirecotry and build them. Note that you must have scons installed. Substitute `<platform>` for `linux` or `windows` depending on your platform.
```
git clone -b 4.2 https://github.com/godotengine/godot-cpp
cd godot-cpp
scons platform=<platform> target=template_release
```

## Windows
Go into `./src` directory, open `ELIZA-GDExtension.vcxproj` in Visual Studio 2022 and hit Build.

## Unix
Go into `./src` directory and run `make`.

## Demo
After compiling the code via either of the methods you will be able to run the demo project in `./demo` and have the library files to include in your own project. `.gdextension` metadata file can be copied from `./demo/bin/eliza.gdextension`.

