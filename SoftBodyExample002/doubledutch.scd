(
s.waitForBoot{ fork{
	~freqBus = Bus.control(s);
	~ampBus = Bus.control(s);

	SynthDef(\detect, {
		arg freqOut, ampOut;
		var amp, freq, hasFreq, in;
		in = SoundIn.ar(0);
		amp = Amplitude.kr(in);
		//amp.ampdb.poll;
		#freq, hasFreq = Pitch.kr(in,median:7);
		Out.kr(freqOut, freq.cpsmidi);
		Out.kr(ampOut, amp.ampdb);
	}).add;

	OSCdef(\getFreqAmp, {
		arg msg;
		var freq, amp;
		freq = ~freqBus.getSynchronous.asFloat;
		amp = ~ampBus.getSynchronous.asFloat;
		~of.sendMsg("/freqAmp", freq, amp);
		//freq.postln;
		//msg.postln;
	}, "/getFreqAmp");

	~of = NetAddr("127.0.0.1", 12321);

	0.1.wait;

	a = Synth(\detect, [\freqOut, ~freqBus, \ampOut, ~ampBus]);
}}
)






