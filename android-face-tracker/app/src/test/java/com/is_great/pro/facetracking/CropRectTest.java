package com.is_great.pro.facetracking;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertNull;

import org.junit.Test;

/** The rectangle of the overlay that is saved as a face image. */
public class CropRectTest {
    private static final int W = 640, H = 480;

    @Test
    public void faceInsideTheImageIsCroppedAsIs() {
        // centre (100, 200), half-size 30 x 40
        assertArrayEquals(new int[] {70, 160, 60, 80}, FaceTrackerActivity.cropRect(100, 200, 30, 40, W, H));
    }

    @Test
    public void faceCrossingAnEdgeIsClippedToTheImage() {
        assertArrayEquals(new int[] {0, 0, 40, 30}, FaceTrackerActivity.cropRect(10, 5, 30, 25, W, H));
        assertArrayEquals(new int[] {610, 450, 30, 30}, FaceTrackerActivity.cropRect(630, 470, 20, 20, W, H));
    }

    @Test
    public void faceOutsideTheImageGivesNothingToCrop() {
        // these used to reach Bitmap.createBitmap with a zero or negative size
        assertNull(FaceTrackerActivity.cropRect(-100, 100, 30, 30, W, H));
        assertNull(FaceTrackerActivity.cropRect(700, 100, 30, 30, W, H));
        assertNull(FaceTrackerActivity.cropRect(100, 600, 30, 30, W, H));
        assertNull(FaceTrackerActivity.cropRect(100, 100, 0, 30, W, H));
    }
}
