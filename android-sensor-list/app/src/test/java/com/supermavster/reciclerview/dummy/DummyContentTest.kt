package com.supermavster.reciclerview.dummy

import android.hardware.Sensor
import android.hardware.SensorManager
import org.junit.Assert.assertEquals
import org.junit.Assert.assertTrue
import org.junit.Test
import org.mockito.Mockito.`when`
import org.mockito.Mockito.mock

/** DummyContent turns the device's sensor list into the items the list shows. */
class DummyContentTest {

    private fun sensor(name: String, type: Int): Sensor {
        val s = mock(Sensor::class.java)
        `when`(s.name).thenReturn(name)
        `when`(s.type).thenReturn(type)
        return s
    }

    private fun managerWith(vararg sensors: Sensor): SensorManager {
        val m = mock(SensorManager::class.java)
        `when`(m.getSensorList(Sensor.TYPE_ALL)).thenReturn(sensors.toList())
        return m
    }

    @Test
    fun oneItemPerSensorInDeviceOrder() {
        val content = DummyContent(managerWith(
            sensor("BMI160 Accelerometer", Sensor.TYPE_ACCELEROMETER),
            sensor("BMI160 Gyroscope", Sensor.TYPE_GYROSCOPE),
            sensor("AK09918 Magnetometer", Sensor.TYPE_MAGNETIC_FIELD)))

        val items = content.getItems()
        assertEquals(listOf("1", "2", "3"), items.map { it.id })
        assertEquals("Sensor #1", items[0].content)
        // details are the sensor's own name and numeric type, not a neighbour's
        assertEquals(arrayListOf("BMI160 Accelerometer", "1"), items[0].details)
        assertEquals(arrayListOf("BMI160 Gyroscope", "4"), items[1].details)
        assertEquals(arrayListOf("AK09918 Magnetometer", "2"), items[2].details)
    }

    @Test
    fun itemsCanBeLookedUpById() {
        val content = DummyContent(managerWith(sensor("Light", Sensor.TYPE_LIGHT)))
        assertEquals("Light", content.ITEM_MAP["1"]?.details?.get(0))
    }

    @Test
    fun noSensorsMeansAnEmptyList() {
        val content = DummyContent(managerWith())
        assertTrue(content.getItems().isEmpty())
        assertTrue(content.ITEM_MAP.isEmpty())
    }
}
