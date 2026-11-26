# android-face-tracker

[![CI](https://github.com/Wil12Fred/university-coursework/actions/workflows/android-face-tracker.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/android-face-tracker.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

Final project for a mobile-devices course: an Android app, based on Google's
Mobile Vision *FaceTracker* sample, that tracks faces in the live camera
preview, labels each with its tracking id, and saves a crop of every newly
tracked face to the app's private storage.

## Features

- Opens the camera (asks for the `CAMERA` permission) and runs the Mobile
  Vision `FaceDetector` on the live preview.
- Draws a box, a centre dot and the face id over every tracked face, and logs
  each id in a scrolling text view.
- Crops each newly tracked face from the overlay and saves it once as
  `face<token>-<faceId>.png` in the app's files directory.

## Requirements

- JDK 8 (Android Gradle Plugin 3.4.1 / Gradle 5.1.1).
  Debian/Ubuntu: `sudo apt install openjdk-8-jdk` where available, or any
  Temurin 8 build; Arch: `sudo pacman -S jdk8-openjdk`.
- Android SDK with `platforms;android-25` and `build-tools;28.0.3`, with
  `ANDROID_HOME` pointing at it.

The project was originally on AGP 2.3.3 / Gradle 3.3, which can no longer be
downloaded; the build files were upgraded to the minimum version that works.

## Build

```sh
export JAVA_HOME=/path/to/jdk8
export ANDROID_HOME=$HOME/Android/Sdk
./gradlew assembleDebug
# -> app/build/outputs/apk/debug/app-debug.apk
```

## Run

Install it on a real device with a camera: `./gradlew installDebug`
(minSdk 19). The built APK, as `aapt dump badging` reports it:

```console
$ aapt dump badging app/build/outputs/apk/debug/app-debug.apk | grep -E 'package|permission|launchable'
package: name='com.is_great.pro.facetracking' versionCode='1' versionName='1.0'
uses-permission: name='android.permission.CAMERA'
launchable-activity: name='com.is_great.pro.facetracking.FaceTrackerActivity'  label='' icon=''
```

## Tests

```sh
./gradlew testDebugUnitTest
```

`CropRectTest` (JVM) covers `FaceTrackerActivity.cropRect`, which turns a
face's centre and half-size into the rectangle of the overlay to save: a face
inside the image is cropped as is, one crossing an edge is clipped to the
image, and one entirely outside (or with zero size) gives nothing to crop.
The camera and the detector need a device and are not tested.

## Project layout

```
app/src/main/java/com/is_great/pro/facetracking/
  FaceTrackerActivity.java      camera + detector setup, face cropping/saving
  FaceGraphic.java              overlay drawing for one face
  ui/camera/CameraSourcePreview.java, GraphicOverlay.java   (from the Google sample)
app/src/test/.../CropRectTest.java
```

## Known limitations

- A face box entirely outside the overlay used to reach
  `Bitmap.createBitmap` with a zero or negative size, which throws; the crop
  now skips it (`cropRect` returns null), with a test.
- Google Mobile Vision (`play-services-vision`) is deprecated in favour of
  ML Kit; on current devices the face detector may not download its model,
  in which case no faces are tracked.
- Uses the deprecated `compile` configuration and the Android Support Library.
- The crop is rendered from the overlay view (`loadBitmapFromView(mOverlay, …)`),
  which only holds the drawn box and text; the camera preview is a separate
  `SurfaceView`, so the saved image probably does not contain the face itself
  (not verified on a device).

## Background

Written for a mobile-devices course at university, 2019.

## License

MIT — see [LICENSE](../LICENSE).
