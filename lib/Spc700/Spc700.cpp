#include "pico/stdlib.h"
#include "pico/time.h"
#include "Spc700.h"

/**
 * Sleeps the system after a GPIO change to give the SPC an opportunity
 * to catch up to the changes in the bus
 */
void spc_wait() {
  sleep_us(10);
}

/**
 * Sets the read/write direction on the SPC
 */
void spc_set_data_direction(bool read) {
  gpio_put(PIN_WRITE, read);
  gpio_put(PIN_READ, !read);
  spc_wait();
}

void spc_set_read_direction() {
  gpio_set_dir_in_masked(DATA_PINS_MASK);
  spc_set_data_direction(true);
}

void spc_set_write_direction() {
  gpio_set_dir_out_masked(DATA_PINS_MASK);
  spc_set_data_direction(false);
}

void spc_init() {
  spc_set_read_direction();
  gpio_set_dir(PIN_READ, true);
  gpio_set_dir(PIN_WRITE, true);

  // set the address lines, setting PA7/6 to the states they'll remain in
  // the whole time
  gpio_set_dir_out_masked(ADDR_PINS_MASK);
  gpio_put(PIN_ADDR_PA7, false);
  gpio_put(PIN_ADDR_PA6, true);
}

void spc_open_addr_port(uint8_t port) {
  // we can only read from one port at a time, so ensure that we're not pulling
  // the line down on any other ports (ports are active low).
  gpio_put_masked(ADDR_PINS_MASK, 0xffffffff);

  // open up the port...
  gpio_put(port, false);
  spc_wait();
}

uint8_t spc_read(uint8_t port) {
  // set the address and data buses up for reading...
  spc_open_addr_port(port);
  spc_set_read_direction();

  // grab the data...
  uint32_t rawData = gpio_get_all();

  // grab only the data bus stuff
  uint8_t retVal = (rawData >> DATA_BIT_OFFSET) & 0xff;

  return retVal;
}

void spc_write(uint8_t port, uint8_t data) {

}
