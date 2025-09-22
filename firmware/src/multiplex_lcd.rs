use embassy_rp::pio::program::pio_file;
use embassy_rp::pio::{
    Common, Config, FifoJoin, Instance, LoadedProgram, PioPin, ShiftConfig, ShiftDirection, StateMachine,
};

const DATA_PINS :i8 = 12;
const COMMON_PINS :i8 = 4;
const TOTAL_PINS :i8 = DATA_PINS + COMMON_PINS;
const DIGITS :i8 = 6;
const WAIT_CYCLES :i8 = 31;

/// This struct represents a LCD program loaded into pio instruction memory.
/// Based on direct driving LCD from this guide:
/// https://ww1.microchip.com/downloads/en/Appnotes/doc8103.pdf
/// To use: Load up the FIFO with bits : COM_DIR+COM_OUT+DATA_OUT
/// The Code will execute wave pattern with 1 COM_PIN at a time with with the data pin according to the sequence of bits from the FIFO
pub struct PioLCDProgram<'a, PIO: Instance> {
    prg: LoadedProgram<'a, PIO>,
}

impl<'a, PIO: Instance> PioLCDProgram<'a, PIO> {
    /// Load the ws2812 program into the given pio
    pub fn new(common: &mut Common<'a, PIO>) -> Self {
        let prg = pio_file!("src/multiplex_lcd.pio");
        let prg = common.load_program(&prg.program);
        Self { prg }
    }
}