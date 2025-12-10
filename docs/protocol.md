# Serial Protocol

The Arduino firmware sends a single byte on every update cycle (default: every 10 ms).

Each bit represents the state of one button on the physical controller.

## Bit Mapping

From least significant bit (bit 0) to bit 5:

- **Bit 0** – UP  
- **Bit 1** – DOWN  
- **Bit 2** – LEFT  
- **Bit 3** – RIGHT  
- **Bit 4** – A  
- **Bit 5** – B  

Bit value:

- `1` → pressed  
- `0` → released  

## Example

If the byte received is:

- `0b00010001` (decimal 17)

Then:

- UP   = 1 (pressed)  
- DOWN = 0  
- LEFT = 0  
- RIGHT= 0  
- A    = 1 (pressed)  
- B    = 0  

## Baud Rate

- Baud rate: `115200`  
- Data bits: 8  
- Stop bits: 1  
- Parity: none  

This configuration must match between the Arduino firmware and the C++ client.
