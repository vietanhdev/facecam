# mlearning-cam
Funny camera app using Machine Learning - Project for Machine Learning and Data Mining course at HUST


## NOTE FOR DEVELOPERS

### 1. Bug of `QString::fromStdString()`

- To convert std::string to QString, the following way causes an error on Windows:

```
QString::fromStdString(string_to_convert);
```

Instead, Use `QString::fromUtf8` like this:
```
QString::fromUtf8(string_to_convert.c_str());
```

## DEVELOPMENT ENVIRONMENT AND BUILD

### Setup for Linux - Ubuntu 18.04

#### Setup

- Install QT:

```
sudo apt-get install build-essential
sudo apt-get install qtcreator
sudo apt-get install qt5-default
sudo apt-get install qt5-doc
sudo apt-get install qt5-doc-html qtbase5-doc-html
sudo apt-get install qtbase5-examples
sudo /sbin/ldconfig -v
```

- Install OpenCV

```
https://linuxize.com/post/how-to-install-opencv-on-ubuntu-18-04/
```

#### Compile and Run

- Compile
```
cd <project directory>
mkdir build
cd build
cmake ..
make
```

- Run
```
./ml-cam
```

### Setup for Windows 10

#### Setup

**NOTE:** You need to correct following paths correctly as your installation.

- Visual Studio 2017

- Install CMake for Windows: https://cmake.org/download/

- Install Gitbash (Optional)

- Install QT: 
    Download and install from this link: https://www.qt.io/download

    + Add QT to PATH:
        C:\Qt\5.12.1\msvc2017_64\bin\

    + Add some environment variables:
        QT_DIR=C:\Qt\5.12.1\msvc2017_64
        QT_QPA_PLATFORM_PLUGIN_PATH=C:\Qt\5.12.1\msvc2017_64\plugins\platforms\

- Compile and install OpenCV 4
    + Add OPENCV_DIR=C:\OpenCV\x64\vc15\staticlib

- **Restart the computer**.


#### Compile and Run

- Use PowerShell:
```
cd <project directory>
mkdir build-win
cd build-win
cmake -G "Visual Studio 15 2017 Win64" ..
```

- Open `build-win\ml-cam.sln` with Visual Studio 2017.

- Set `ml-cam` as StartUp project. (Right click `ml-cam` project > Set as StartUp project)

- Right click `ml-cam` project > **Properties** > **Configuration Properties** > **C/C++** > **Code Generation** >  Set **Runtime Library** to `Multi-threaded (/MT)`.

- Build project with Visual Studio 2017.

- Deploy QT dlls:

```
cd build-win\Debug
windeployqt.exe  .\ml-cam.exe
```

- **NOTE**:
    + If you build with Release mode, `cd build-win\Release`.
    + Only after you run `windeployqt.exe  .\ml-cam.exe` successfully, you can run the excutable file `ml-cam.exe`.