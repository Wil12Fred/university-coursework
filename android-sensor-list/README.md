# android-sensor-list

[![CI](https://github.com/Wil12Fred/university-coursework/actions/workflows/android-sensor-list.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/android-sensor-list.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

A small Kotlin Android app from a mobile-device programming lab: it lists
every sensor the device reports in a `RecyclerView` and, on tap, uses the
Navigation component to show that sensor's name and type.

## Features

- Asks the `SensorManager` for every sensor (`Sensor.TYPE_ALL`) and shows them
  as `Sensor #1`, `Sensor #2`, …
- Tapping one opens a detail fragment with the sensor's name and numeric type,
  and a *Cerrar* (close) button to go back.

The app id (`com.supermavster.reciclerview`) and class names come from the
Android Studio "list fragment" template the exercise started from.

## Requirements

- JDK 8 (Android Gradle Plugin 3.4.1 / Gradle 5.1.1 do not run on modern JDKs).
  Debian/Ubuntu: `sudo apt install openjdk-8-jdk` where available, or any
  Temurin 8 build; Arch: `sudo pacman -S jdk8-openjdk`.
- Android SDK with `platforms;android-28` and `build-tools;28.0.3`, with
  `ANDROID_HOME` pointing at it (from Android Studio or the command-line tools).

## Build

```sh
export JAVA_HOME=/path/to/jdk8
export ANDROID_HOME=$HOME/Android/Sdk
./gradlew assembleDebug
# -> app/build/outputs/apk/debug/app-debug.apk
```

## Run

`./gradlew installDebug` installs it on a connected device or emulator
(minSdk 19). The built APK, as `aapt dump badging` reports it:

```console
$ aapt dump badging app/build/outputs/apk/debug/app-debug.apk | head -4
package: name='com.supermavster.reciclerview' versionCode='1' versionName='1.0' compileSdkVersion='28' compileSdkVersionCodename='9'
sdkVersion:'19'
targetSdkVersion:'28'
application-label:'ReciclerView'
```

## Tests

```sh
./gradlew testDebugUnitTest
```

`DummyContentTest` (JVM, Mockito) feeds `DummyContent` a mocked
`SensorManager` and checks that it makes one item per sensor in device order,
with ids `1…n`, titles `Sensor #i`, and each item's details holding *its own*
sensor's name and type; that items can be looked up by id; and that no
sensors means an empty list. There are no instrumented tests in CI.

## Project layout

```
app/src/main/java/com/supermavster/reciclerview/
  MainActivity.kt                 hosts the navigation graph
  ItemFragment.kt                 the sensor list
  MyItemRecyclerViewAdapter.kt    RecyclerView adapter
  ShowData.kt                     detail fragment (name + type)
  dummy/DummyContent.kt           builds the list from SensorManager
app/src/main/res/navigation/navigation.xml
app/src/test/.../DummyContentTest.kt
```

## Known limitations

- Built on the deprecated Android Support Library, `kotlin-android-extensions`
  and `jcenter()`; the toolchain needs JDK 8.
- The detail screen shows the type as a number (e.g. `1` for the
  accelerometer), not its name.
- Leftover template code (`ShowData.newInstance`, unused listeners).

## Background

Written for a mobile-device programming course at university, 2019.

## License

MIT — see [LICENSE](../LICENSE).
