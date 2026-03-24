//! This example test the RP Pico on board LED.
//!
//! It does not work with the RP Pico W board. See wifi_blinky.rs.
#![no_std]
#![no_main]

mod multiplex_lcd;

use defmt::*;
use embassy_executor::Spawner;
use embassy_rp::gpio;
use embassy_rp::i2c;
use embassy_time::Timer;
use gpio::{Level, Output};
use {defmt_rtt as _, panic_probe as _};
use ds3231::DS3231;

const RTC_CONFIG: ds3231::Config =  ds3231::Config{
    time_representation: ds3231::TimeRepresentation::TwentyFourHour,
    square_wave_frequency: ds3231::SquareWaveFrequency::Hz1,
    interrupt_control: ds3231::InterruptControl::SquareWave,
    battery_backed_square_wave: false,
    oscillator_enable: ds3231::Oscillator::Enabled,
};


#[embassy_executor::main]
async fn main(_spawner: Spawner) {
    let p = embassy_rp::init(Default::default());
    let mut led = Output::new(p.PIN_25, Level::Low);

	// Setup The DS3231 Real Time Clock
	let sda = p.PIN_14; //TODO check pins
    let scl = p.PIN_15;
	let i2c = i2c::I2c::new_blocking(p.I2C1, scl, sda, i2c::Config::default()); //TODO check p.I2C0 or p.I2C1
	let mut rtc = DS3231::new(i2c, 0x68);
	rtc.configure(&RTC_CONFIG).expect("Error setting up RTC");

    loop {
        info!("led on!");
        led.set_high();
        Timer::after_secs(1).await;

        info!("led off!");
        led.set_low();
        Timer::after_secs(1).await;
    }
}
