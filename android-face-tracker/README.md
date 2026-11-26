# DispositivosMoviles – face tracking demo (Android)

Final project for a mobile-devices course (*Dispositivos Móviles*, October 2019),
based on Google's Mobile Vision *FaceTracker* sample. The app:

- opens the camera (asks for the `CAMERA` permission) and runs the Mobile Vision
  `FaceDetector` on the live preview;
- draws a box, a centre dot and the face id over every tracked face;
- crops each newly tracked face from the overlay and saves it once as
  `<faceId>.png` in the app's private files directory.

Note: Google Mobile Vision (`play-services-vision`) has been deprecated in
favour of ML Kit; on current devices the face detector may not download its
model, in which case no faces are tracked.

## Requirements

- JDK 8 (Android Gradle Plugin 3.4.1 / Gradle 5.1.1)
- Android SDK with `platforms;android-25` and `build-tools;28.0.3`,
  `ANDROID_HOME` pointing at it

The project was originally on AGP 2.3.3 / Gradle 3.3, which can no longer be
downloaded; the build files were upgraded to the minimum version that works.

## Build

```sh
export JAVA_HOME=/path/to/jdk8
export ANDROID_HOME=$HOME/Android/Sdk
./gradlew assembleDebug testDebugUnitTest
# -> app/build/outputs/apk/debug/app-debug.apk
```

Run it on a real device with a camera: `./gradlew installDebug` (minSdk 19).
The only tests are the Android Studio template examples.

## Layout

```
app/src/main/java/com/is_great/pro/facetracking/
  FaceTrackerActivity.java      camera + detector setup, face cropping/saving
  FaceGraphic.java              overlay drawing for one face
  ui/camera/CameraSourcePreview.java, GraphicOverlay.java   (from the Google sample)
```
