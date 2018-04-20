
(
s.waitForBoot{ fork{
	// GROUPS ///////////////////////////////////////////////
	s.sendMsg(\g_new, 1999); s.sendMsg(\g_new, 2000);
	10.do{|ix| s.sendMsg(\g_new, 2001+ix, 3, 2000+ix)};
	s.sendMsg(\g_new, 2999, 3, 2010);

	~kbus = 0;

	//// phasorclock synthdef ////////////////////////////////////////////////////////////////////////
	SynthDef(\phasorclock, {
		arg abus, kbus, trigbus, stbpm=60.0, endbpm=60.0, rampdur=0.05, bpc=16.0, t_tr=1, dir=1;
		var temporamp = EnvGen.ar( Env.new( [1.0, 0.0, 1.0], [0.0, rampdur] ), t_tr ).linexp(0.0, 1.0, stbpm, endbpm);
		var tempo = (temporamp/60.0) / (SampleRate.ir*bpc);
		var clk = Phasor.ar( In.kr(trigbus), tempo*dir);
		Out.ar(abus, clk);
		Out.kr(kbus, clk);
	}).add;

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// OSCdefs for Sending Control Data from Control Busses to Processing
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	OSCdef( \getkdata, { |msg time addr recvPort|
		var id = msg[1].asSymbol;
		var kbus = ~broadcastList[id][1].asInteger;
		s.sendMsg(\c_get, kbus);
	}, "/getkdata");


	OSCdef( \kdat,
		{ |msg time addr recvPort|
			var bus = msg[1].asInteger;
			var val = msg[2].asFloat;
			var id, blist;
			blist = ~broadcastList.asSortedArray;
			blist.do(
				{ |it ix|
					if( it[1][1].asInteger == bus,
						{
							NetAddr(~broadcastList[ it[0] ][0].ip, 12321).sendMsg("/kdat", val);
						}
					);
				}
			);
		},
		\c_set);



	~broadcastList = ();


	OSCdef(\joinBroadcast, { |msg time addr recvPort|
		var id = msg[1].asSymbol;
		var ip = addr;
		var dArray;
		msg.postln;
		time.postln;
		addr.postln;
		recvPort.postln;
		//see if id is already used
		if( ~broadcastList.includesKey(id), { NetAddr(ip.ip, 12321).sendMsg("/reply", "Sorry, that ID is taken. Please choose another") },
			{ //if not id is not already used
				~broadcastList.put(id, [ip, ~kbus]);
				~kbus = ~kbus + 1;
				//post complete list
				dArray = ~broadcastList.asSortedArray;
				dArray.do({|it ix| it[0].post; " : ".post; it[1].postln});
		});
	}, "/id");

	0.1.wait;

	// 1) Make phasorclock
	99.do{ |ix|
		s.sendMsg(\s_new, \phasorclock, 3000+ix, 0, 2002, \abus, 100+ix, \kbus, ix, \trigbus, 350+ix, \stbpm, 60, \endbpm, 60, \bpc, 8);
	};


}}
)

NetAddr(~broadcastList[\jyang][0].ip, 12321).sendMsg("/bounce", 17.0, 0.08);

n= NetAddr("127.0.0.1", 57120);
n.sendMsg("/id", \jyang2);

n.sendMsg("/getkdata", \jyang);