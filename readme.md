
# HapticSensor

    A class that interprets touch sensation as vibration for a prosthetic or remotely operated device.

    This version of the software supports an array of four HapticSensor units. Each receives input from a capacitive sensor which is processed by first storing the signal on the top of on array holding the last sixteen readings. The signals are interpreted by a decaying waveform that provides a historical reference for deriving the relative intensity of the next reading, which is output as haptic feeback via a small button vibrator. These small motors are the same kind found in cell phones. The generated signal simulates the experience of natural sensation. The feedback intensity level corresponds to the pressure of the touch, lingering a moment, although quickly fading away.

    The math came from an open source project run by a physics and math scientist calling himself Dr. O. The original software that I got from him was set up for an atmoshperic pressure sensor and a vibrator for feedback, although he was experimenting with other sensors, too. I began adapting the softwre to support arrays of sensors and corresponding feedback devices. Since then, Dr. O's original project has dissappeared. Wishing to explore brain/body awarenes, and possibilities for extending the human sensorium for prosthetic or cybernetic devices, I have continued experimental work. Pairing sensors with haptic response devices of different types, I have spent my spare time iterating designs and software since 2014. This version shows a little promise and so I share it. I have seem similar and very exciting work being done in medical research with bionic arms. I hope others may find this repo and perhaps help advance this concept as open source. Or maybe collaborate, or just provide some feedback for better manipulation of the math.

    copyright December 2017   by Jon A. Nuljon,  https://nuljon.com
   licensed with GNU LGPLv3 https://choosealicense.com/licenses/lgpl-3.0/