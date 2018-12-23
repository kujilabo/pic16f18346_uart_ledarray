#ifndef ISR_H_INCLUDED
#define ISR_H_INCLUDED

/**
 * Reads some number of bytes from the receiving buffer and stores them into buffer array data.
 * The number of bytes actually read is returned as an integer.
 *    
 * @param data the buffer into which the data is read
 * @param size the maximum number of bytes to read
 * 
 * @return the total number of bytes read into the buffer.
 */
unsigned char get_rx_data(char * data, unsigned char size);

/**
 * Return 1 if data is received.
 * 
 * @return return 1 if data is received.
 */
unsigned char get_rx_flag();

#endif
