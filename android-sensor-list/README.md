# PDM-Practica1 – Android sensor list

First lab assignment ("Práctica 1") for a mobile-device programming course
(*Programación de Dispositivos Móviles*, 2019). A small Kotlin Android app that:

- asks the `SensorManager` for every sensor on the device and shows them in a
  `RecyclerView` (`Sensor #1`, `Sensor #2`, …);
- on tap, uses the Navigation component to open a detail fragment with the
  sensor's name and numeric type, and a *Cerrar* (close) button to go back.

The app id (`com.supermavster.reciclerview`) and class names come from the
Android Studio "list fragment" template the exercise started from.

## Requirements

- JDK 8 (Android Gradle Plugin 3.4.1 / Gradle 5.1.1 do not run on modern JDKs)
- Android SDK with `platforms;android-28` and `build-tools;28.0.3`, with
  `ANDROID_HOME` pointing at it

## Build

```sh
export JAVA_HOME=/path/to/jdk8
export ANDROID_HOME=$HOME/Android/Sdk
./gradlew assembleDebug testDebugUnitTest
# -> app/build/outputs/apk/debug/app-debug.apk
```

`./gradlew installDebug` installs it on a connected device (minSdk 19). The only
tests are the Android Studio template examples.

## Layout

```
app/src/main/java/com/supermavster/reciclerview/
  MainActivity.kt                 hosts the navigation graph
  ItemFragment.kt                 the sensor list
  MyItemRecyclerViewAdapter.kt    RecyclerView adapter
  ShowData.kt                     detail fragment (name + type)
  dummy/DummyContent.kt           builds the list from SensorManager
app/src/main/res/navigation/navigation.xml
```
