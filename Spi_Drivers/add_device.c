#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/spi/spi.h>

/* MODULE PARAMETERS */
static uint spi_bus = 4;
static uint spi_cs = 0;
static uint spi_speed_hz = 1500000;
static uint spi_bits_per_word = 16;

/* THIS IS WHERE YOUR DEVICE IS CREATED; THROUGH THIS YOU INTERACT WITH YOUR EXTERNAL DEVICE */
static struct spi_device *spi_device;


/* SETUP SPI */

static inline __init int spi_init(void) {
    struct spi_board_info spi_device_info = {
        .modalias = "module name",
        .max_speed_hz = spi_speed_hz,
        .bus_num = spi_bus,
        .chip_select = spi_cs,
        .mode = 0,
    };

    struct spi_master *master;

    int ret;

    // get the master device, given SPI the bus number
    master = spi_busnum_to_master( spi_device_info.bus_num );
    if( !master )
        return -ENODEV;

    // create a new slave device, given the master and device info
    spi_device = spi_new_device( master, &spi_device_info );
    if( !spi_device )
        return -ENODEV;

    spi_device->bits_per_word = spi_bits_per_word;

    ret = spi_setup( spi_device );
    if( ret )
        spi_unregister_device( spi_device );

    return ret;
}

static inline void spi_exit(void) {
    spi_unregister_device( spi_device );
}

/*To write data to your device:

spi_write( spi_device, &write_data, sizeof write_data );*/
