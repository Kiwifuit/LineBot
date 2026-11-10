# Line following bot Notes

## Pin assignments

| Module | Function | Pin (m328p) | Physical Pin# (m328p) |
| ------ | -------- | ----------- | ------------- |
| Motor Driver | PWM | PD3 | D3 |
| Motor Driver | Direction | PC[0..3] | D[14..17] / A[0..3] |
| Motor Driver | Standby | PB4 | D12 |
| IR Array | Array Input | PD[4..7] (low byte), PB[0..3] (high byte) | D[4..7], D[8..11] |

## Nano Pinout

![Arduino Nano pinout](./doc/pinout-nano.png)
