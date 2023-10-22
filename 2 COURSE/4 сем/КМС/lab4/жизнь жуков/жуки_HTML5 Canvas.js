(function (cjs, an) {

var p; // shortcut to reference prototypes
var lib={};var ss={};var img={};
lib.ssMetadata = [
		{name:"жуки_HTML5 Canvas_atlas_1", frames: [[119,120,115,115],[236,139,53,56],[244,0,119,137],[0,0,242,118],[365,138,48,62],[291,139,58,51],[342,202,64,45],[291,192,49,60],[119,237,62,46],[415,193,43,67],[415,138,56,53],[474,0,29,136],[473,138,29,29],[183,237,69,40],[473,169,29,29],[365,0,107,136],[0,120,117,117],[0,239,65,33]]}
];


(lib.AnMovieClip = function(){
	this.currentSoundStreamInMovieclip;
	this.actionFrames = [];
	this.soundStreamDuration = new Map();
	this.streamSoundSymbolsList = [];

	this.gotoAndPlayForStreamSoundSync = function(positionOrLabel){
		cjs.MovieClip.prototype.gotoAndPlay.call(this,positionOrLabel);
	}
	this.gotoAndPlay = function(positionOrLabel){
		this.clearAllSoundStreams();
		this.startStreamSoundsForTargetedFrame(positionOrLabel);
		cjs.MovieClip.prototype.gotoAndPlay.call(this,positionOrLabel);
	}
	this.play = function(){
		this.clearAllSoundStreams();
		this.startStreamSoundsForTargetedFrame(this.currentFrame);
		cjs.MovieClip.prototype.play.call(this);
	}
	this.gotoAndStop = function(positionOrLabel){
		cjs.MovieClip.prototype.gotoAndStop.call(this,positionOrLabel);
		this.clearAllSoundStreams();
	}
	this.stop = function(){
		cjs.MovieClip.prototype.stop.call(this);
		this.clearAllSoundStreams();
	}
	this.startStreamSoundsForTargetedFrame = function(targetFrame){
		for(var index=0; index<this.streamSoundSymbolsList.length; index++){
			if(index <= targetFrame && this.streamSoundSymbolsList[index] != undefined){
				for(var i=0; i<this.streamSoundSymbolsList[index].length; i++){
					var sound = this.streamSoundSymbolsList[index][i];
					if(sound.endFrame > targetFrame){
						var targetPosition = Math.abs((((targetFrame - sound.startFrame)/lib.properties.fps) * 1000));
						var instance = playSound(sound.id);
						var remainingLoop = 0;
						if(sound.offset){
							targetPosition = targetPosition + sound.offset;
						}
						else if(sound.loop > 1){
							var loop = targetPosition /instance.duration;
							remainingLoop = Math.floor(sound.loop - loop);
							if(targetPosition == 0){ remainingLoop -= 1; }
							targetPosition = targetPosition % instance.duration;
						}
						instance.loop = remainingLoop;
						instance.position = Math.round(targetPosition);
						this.InsertIntoSoundStreamData(instance, sound.startFrame, sound.endFrame, sound.loop , sound.offset);
					}
				}
			}
		}
	}
	this.InsertIntoSoundStreamData = function(soundInstance, startIndex, endIndex, loopValue, offsetValue){ 
 		this.soundStreamDuration.set({instance:soundInstance}, {start: startIndex, end:endIndex, loop:loopValue, offset:offsetValue});
	}
	this.clearAllSoundStreams = function(){
		var keys = this.soundStreamDuration.keys();
		for(var i = 0;i<this.soundStreamDuration.size; i++){
			var key = keys.next().value;
			key.instance.stop();
		}
 		this.soundStreamDuration.clear();
		this.currentSoundStreamInMovieclip = undefined;
	}
	this.stopSoundStreams = function(currentFrame){
		if(this.soundStreamDuration.size > 0){
			var keys = this.soundStreamDuration.keys();
			for(var i = 0; i< this.soundStreamDuration.size ; i++){
				var key = keys.next().value; 
				var value = this.soundStreamDuration.get(key);
				if((value.end) == currentFrame){
					key.instance.stop();
					if(this.currentSoundStreamInMovieclip == key) { this.currentSoundStreamInMovieclip = undefined; }
					this.soundStreamDuration.delete(key);
				}
			}
		}
	}

	this.computeCurrentSoundStreamInstance = function(currentFrame){
		if(this.currentSoundStreamInMovieclip == undefined){
			if(this.soundStreamDuration.size > 0){
				var keys = this.soundStreamDuration.keys();
				var maxDuration = 0;
				for(var i=0;i<this.soundStreamDuration.size;i++){
					var key = keys.next().value;
					var value = this.soundStreamDuration.get(key);
					if(value.end > maxDuration){
						maxDuration = value.end;
						this.currentSoundStreamInMovieclip = key;
					}
				}
			}
		}
	}
	this.getDesiredFrame = function(currentFrame, calculatedDesiredFrame){
		for(var frameIndex in this.actionFrames){
			if((frameIndex > currentFrame) && (frameIndex < calculatedDesiredFrame)){
				return frameIndex;
			}
		}
		return calculatedDesiredFrame;
	}

	this.syncStreamSounds = function(){
		this.stopSoundStreams(this.currentFrame);
		this.computeCurrentSoundStreamInstance(this.currentFrame);
		if(this.currentSoundStreamInMovieclip != undefined){
			var soundInstance = this.currentSoundStreamInMovieclip.instance;
			if(soundInstance.position != 0){
				var soundValue = this.soundStreamDuration.get(this.currentSoundStreamInMovieclip);
				var soundPosition = (soundValue.offset?(soundInstance.position - soundValue.offset): soundInstance.position);
				var calculatedDesiredFrame = (soundValue.start)+((soundPosition/1000) * lib.properties.fps);
				if(soundValue.loop > 1){
					calculatedDesiredFrame +=(((((soundValue.loop - soundInstance.loop -1)*soundInstance.duration)) / 1000) * lib.properties.fps);
				}
				calculatedDesiredFrame = Math.floor(calculatedDesiredFrame);
				var deltaFrame = calculatedDesiredFrame - this.currentFrame;
				if(deltaFrame >= 2){
					this.gotoAndPlayForStreamSoundSync(this.getDesiredFrame(this.currentFrame,calculatedDesiredFrame));
				}
			}
		}
	}
}).prototype = p = new cjs.MovieClip();
// symbols:



(lib.CachedBmp_24 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(0);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_19 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(1);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_23 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(2);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_25 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(3);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_18 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(4);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_20 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(5);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_21 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(6);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_16 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(7);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_14 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(8);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_17 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(9);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_15 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(10);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_12 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(11);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_9 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(12);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_22 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(13);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_8 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(14);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_11 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(15);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_7 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(16);
}).prototype = p = new cjs.Sprite();



(lib.CachedBmp_10 = function() {
	this.initialize(ss["жуки_HTML5 Canvas_atlas_1"]);
	this.gotoAndStop(17);
}).prototype = p = new cjs.Sprite();



(lib._return = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Слой_1
	this.instance = new lib.CachedBmp_25();
	this.instance.setTransform(-0.5,-0.5,0.5,0.5);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(1));

	this._renderFirstFrame();

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(-0.5,-0.5,121,59);


(lib.Стоп = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Слой_1
	this.instance = new lib.CachedBmp_24();
	this.instance.setTransform(0,0,0.5,0.5);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(1));

	this._renderFirstFrame();

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(0,0,57.5,57.5);


(lib.Старт = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Слой_1
	this.instance = new lib.CachedBmp_23();
	this.instance.setTransform(-0.5,-0.5,0.5,0.5);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(1));

	this._renderFirstFrame();

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(-0.5,-0.5,59.5,68.5);


(lib.Лапа = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Layer_1
	this.instance = new lib.CachedBmp_22();
	this.instance.setTransform(-34,0,0.5,0.5);

	this.instance_1 = new lib.CachedBmp_14();
	this.instance_1.setTransform(-30.65,0,0.5,0.5);

	this.instance_2 = new lib.CachedBmp_15();
	this.instance_2.setTransform(-27.3,-0.05,0.5,0.5);

	this.instance_3 = new lib.CachedBmp_16();
	this.instance_3.setTransform(-24.05,-0.15,0.5,0.5);

	this.instance_4 = new lib.CachedBmp_17();
	this.instance_4.setTransform(-20.75,-0.25,0.5,0.5);

	this.instance_5 = new lib.CachedBmp_18();
	this.instance_5.setTransform(-23.4,-0.15,0.5,0.5);

	this.instance_6 = new lib.CachedBmp_19();
	this.instance_6.setTransform(-26,-0.1,0.5,0.5);

	this.instance_7 = new lib.CachedBmp_20();
	this.instance_7.setTransform(-28.65,-0.05,0.5,0.5);

	this.instance_8 = new lib.CachedBmp_21();
	this.instance_8.setTransform(-31.35,0,0.5,0.5);

	this.timeline.addTween(cjs.Tween.get({}).to({state:[{t:this.instance}]}).to({state:[{t:this.instance_1}]},1).to({state:[{t:this.instance_2}]},1).to({state:[{t:this.instance_3}]},1).to({state:[{t:this.instance_4}]},1).to({state:[{t:this.instance_5}]},1).to({state:[{t:this.instance_6}]},1).to({state:[{t:this.instance_7}]},1).to({state:[{t:this.instance_8}]},1).to({state:[{t:this.instance}]},1).wait(1));

	this._renderFirstFrame();

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(-34,-0.2,34.8,33.5);


(lib.Жук = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// insects_beetle_icon_icons_com_72451_svg
	this.instance = new lib.CachedBmp_12();
	this.instance.setTransform(53.4,24.65,0.5,0.5);

	this.instance_1 = new lib.CachedBmp_11();
	this.instance_1.setTransform(33.65,24.65,0.5,0.5);

	this.instance_2 = new lib.CachedBmp_10();
	this.instance_2.setTransform(43.85,10.15,0.5,0.5);

	this.instance_3 = new lib.CachedBmp_9();
	this.instance_3.setTransform(36.55,0,0.5,0.5);

	this.instance_4 = new lib.CachedBmp_8();
	this.instance_4.setTransform(69.2,0,0.5,0.5);

	this.timeline.addTween(cjs.Tween.get({}).to({state:[{t:this.instance_4},{t:this.instance_3},{t:this.instance_2},{t:this.instance_1},{t:this.instance}]}).wait(1));

	this._renderFirstFrame();

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(33.7,0,53.5,92.7);


(lib.Жукидетъ = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	// Слой_1
	this.instance = new lib.Жук("synched",0);
	this.instance.setTransform(5.55,-11.95,1,1,0,0,0,60.3,46.4);

	this.timeline.addTween(cjs.Tween.get(this.instance).wait(60));

	// Слой_2
	this.instance_1 = new lib.Лапа("synched",0);
	this.instance_1.setTransform(31.45,12.15,1,1,0,0,180,-0.6,1);

	this.instance_2 = new lib.Лапа("synched",0);
	this.instance_2.setTransform(31.15,-6.75,1,1,0,-14.9983,165.0017,-1.5,0.6);

	this.instance_3 = new lib.Лапа("synched",0);
	this.instance_3.setTransform(31.55,-22.5,1,1,0,-43.2026,136.7974,-0.4,0.8);

	this.instance_4 = new lib.Лапа("synched",0);
	this.instance_4.setTransform(-20.35,13.65,1,1,0,0,0,-1.5,1.2);

	this.instance_5 = new lib.Лапа("synched",0);
	this.instance_5.setTransform(-20.65,-5.45,1,1,14.9983,0,0,-1.5,0.6);

	this.instance_6 = new lib.Лапа("synched",7);
	this.instance_6.setTransform(-20.25,-20.8,1,1,43.2026,0,0,-0.6,1.6);

	this.timeline.addTween(cjs.Tween.get({}).to({state:[{t:this.instance_6},{t:this.instance_5,p:{startPosition:0}},{t:this.instance_4,p:{startPosition:0}},{t:this.instance_3,p:{startPosition:0}},{t:this.instance_2,p:{startPosition:0}},{t:this.instance_1,p:{startPosition:0}}]}).to({state:[{t:this.instance_6},{t:this.instance_5,p:{startPosition:2}},{t:this.instance_4,p:{startPosition:9}},{t:this.instance_3,p:{startPosition:2}},{t:this.instance_2,p:{startPosition:3}},{t:this.instance_1,p:{startPosition:5}}]},29).wait(31));

	this._renderFirstFrame();

}).prototype = p = new cjs.MovieClip();
p.nominalBounds = new cjs.Rectangle(-57.1,-58.3,126.30000000000001,104);


// stage content:
(lib.жуки_HTML5Canvas = function(mode,startPosition,loop) {
	this.initialize(mode,startPosition,loop,{});

	this.actionFrames = [0,26,29];
	this.streamSoundSymbolsList[0] = [{id:"zhuzhzhaniezhuka",startFrame:0,endFrame:60,loop:1,offset:0}];
	this.streamSoundSymbolsList[26] = [{id:"simplyclever",startFrame:26,endFrame:60,loop:1,offset:0}];
	this.streamSoundSymbolsList[29] = [{id:"Sound_05773",startFrame:29,endFrame:60,loop:1,offset:0}];
	// timeline functions:
	this.frame_0 = function() {
		this.clearAllSoundStreams();
		 
		var soundInstance = playSound("zhuzhzhaniezhuka",0);
		this.InsertIntoSoundStreamData(soundInstance,0,60,1);
		/*this.stop();*/
		this.startb.addEventListener("click",f1.bind(this));
		function f1(args){this.play();}
		this.stopb.addEventListener("click",f2.bind(this));
		function f2(args) {this.stop();}
		this.returnb.addEventListener("click",f3.bind(this));
		function f3(args) {this.gotoAndStop(0);}
		startb.addEventListener(MouseEvent.CLICK, function(e){play()});
		stopb.addEventListener(MouseEvent.CLICK, function(e){stop()});
		returnb.addEventListener(MouseEvent.CLICK, function(e){gotoAndStop(0)});
	}
	this.frame_26 = function() {
		var soundInstance = playSound("simplyclever",0);
		this.InsertIntoSoundStreamData(soundInstance,26,60,1);
	}
	this.frame_29 = function() {
		var soundInstance = playSound("Sound_05773",0);
		this.InsertIntoSoundStreamData(soundInstance,29,60,1);
	}

	// actions tween:
	this.timeline.addTween(cjs.Tween.get(this).call(this.frame_0).wait(26).call(this.frame_26).wait(3).call(this.frame_29).wait(31));

	// buttons
	this.returnb = new lib._return();
	this.returnb.name = "returnb";
	this.returnb.setTransform(409.1,39.3,1,1,0,0,0,60,29);
	new cjs.ButtonHelper(this.returnb, 0, 1, 1);

	this.startb = new lib.Старт();
	this.startb.name = "startb";
	this.startb.setTransform(213.8,39.3,1,1,0,0,0,29.2,33.8);
	new cjs.ButtonHelper(this.startb, 0, 1, 1);

	this.stopb = new lib.Стоп();
	this.stopb.name = "stopb";
	this.stopb.setTransform(292.9,36.65,1,1,0,0,0,28.8,28.8);
	new cjs.ButtonHelper(this.stopb, 0, 1, 1);

	this.instance = new lib.CachedBmp_7();
	this.instance.setTransform(263.6,7.35,0.5,0.5);

	this.timeline.addTween(cjs.Tween.get({}).to({state:[{t:this.instance},{t:this.stopb},{t:this.startb},{t:this.returnb}]}).wait(60));

	// Слой_13
	this.instance_1 = new lib.Жукидетъ();
	this.instance_1.setTransform(596.8,431.7,0.1214,0.1214,-77.689,0,0,-0.8,-48.2);

	this.timeline.addTween(cjs.Tween.get(this.instance_1).to({guide:{path:[596.7,431.7,552.3,425.3,510.4,410,470.8,395.5,446,358.9,422.2,323.7,396,290.1,369.6,256.1,329.1,242.5,288.7,228.8,246,235.5,202,242.4,158.9,253,114,263.9,71.6,246.1,31.9,229.4,-8.5,214.8,-35.7,204.8,-63.4,196.4], orient:'fixed'}},59).wait(1));

	// Слой_12
	this.instance_2 = new lib.Жукидетъ();
	this.instance_2.setTransform(35.5,-25.4,0.2588,0.2588,140.0171,0,0,4.8,-55.2);

	this.timeline.addTween(cjs.Tween.get(this.instance_2).to({regY:-55.6,rotation:89.2467,guide:{path:[35.6,-25.4,66.9,2.4,88.6,38,114,79.7,159.8,87.6,203.9,95.3,246.6,82.1,290.2,68.6,331.2,83.9,347.1,89.9,358.4,102.5,387.7,134.9,409.3,173.6,430.6,211.7,454.5,248.1,475.4,280,507.4,301.6,546.9,328.1,593.9,327.9,639.4,327.7,684.9,327.7,686.7,327.7,688.4,327.7], orient:'fixed'}},59).wait(1));

	// Слой_14
	this.instance_3 = new lib.Жукидетъ();
	this.instance_3.setTransform(474.4,479.65,0.269,0.269,-97.454,0,0,3.9,-47.1);

	this.timeline.addTween(cjs.Tween.get(this.instance_3).to({regX:3.8,regY:-47.2,rotation:-127.4517,x:-46.5,y:403.95},59).wait(1));

	// Слой_15
	this.instance_4 = new lib.Жукидетъ();
	this.instance_4.setTransform(666.6,52.65,0.4586,0.4586,-95.2485,0,0,3.9,-45);

	this.timeline.addTween(cjs.Tween.get(this.instance_4).to({regX:4,regY:-45.1,scaleX:0.4585,scaleY:0.4585,rotation:-58.0363,guide:{path:[666.6,52.9,634.4,54.9,603.7,47.1,560.5,36.1,515.3,38.1,471.9,40.1,428.6,34.2,396.6,29.9,364.3,27.4,326.6,24.5,293,9.6,253.6,-8.1,217.5,-33.3], orient:'fixed'}},59).wait(1));

	// Слой_16
	this.instance_5 = new lib.Жукидетъ();
	this.instance_5.setTransform(489.05,555.85,0.2052,0.2052,0,0,0,7,-41.6);

	this.timeline.addTween(cjs.Tween.get(this.instance_5).to({regX:7.2,regY:-41.7,rotation:-30.0012,x:230.35,y:-26.15},59).wait(1));

	// Слой_4
	this.instance_6 = new lib.Жукидетъ();
	this.instance_6.setTransform(-101.2,292,0.2787,0.2787,66.2442,0,0,3.5,-46.1);

	this.timeline.addTween(cjs.Tween.get(this.instance_6).to({regY:-46,rotation:21.2469,guide:{path:[-101.1,292,-93.5,288.9,-85.9,285.7,-79.4,282.4,-72.9,279,-72.4,279,-71.8,279,-69.2,277.9,-66.6,276.8,-66.6,275.7,-66.6,274.5,-64.9,274.5,-63.2,274.5,-54.7,269.3,-46.1,264.1,-44.4,264.1,-42.7,264.1,-40.5,262.6,-38.2,261.1,-15.1,249.7,8.4,262.9,11.1,264.4,14.2,265.4,37.1,272.4,60.3,269.8,74.5,268.3,87.5,262.4,93.2,259.9,99.1,258.1,108.8,253.1,118.5,248.1,135.4,240.9,153,237.3,156.9,236.5,160.8,237.5,171.3,240.3,182.3,241.7,189.2,242.6,195.7,241.4,197,239,198.3,236.5,198.6,236.5,199,236.5,199,231.7,199,226.9]}},29).to({regX:3.6,regY:-45.8,scaleX:0.2285,rotation:0,skewX:21.2469,skewY:-158.7535,guide:{path:[199.1,227,199.1,226.9,199.1,226.9]}},3).to({regX:3.5,regY:-46,scaleX:0.2787,rotation:21.2469,skewX:0,skewY:0,guide:{path:[199.1,226.9,199.1,229.4,199.1,232]}},3).to({regX:3.3,regY:-46.1,rotation:194.1914,guide:{path:[199,231.9,199,229.4,199,226.8,200.8,225.7,202.7,224.6,204,227.8,205.3,230.9,209,245.1,212.8,259.2,212.8,259.8,212.8,260.4,224.8,283.8,242.3,304.1,247,309.6,250.3,316,266.4,347.4,264.7,383,264,397.3,263.7,411.6,263.5,423.3,261.6,434.5]}},24).wait(1));

	// Слой_1
	this.instance_7 = new lib.Жукидетъ();
	this.instance_7.setTransform(-32.5,78.75,0.5873,0.5873,90,0,0,6,-58.3);

	this.timeline.addTween(cjs.Tween.get(this.instance_7).to({regY:-58.4,rotation:71.7529,guide:{path:[-32.4,78.8,-4.6,76,23.1,73.1,22.3,90.4,25.8,106.6,33,139.4,71.5,127.9,99.1,119.7,127.3,110.7,175.2,95.5,219,112.3,196.1,156.7,173.1,201,222.9,219.1,271.4,189.9,306.3,168.8,340.8,146.3,393.7,112,454,109,457,116,460,123,468.1,133,481.1,134.6,517.8,139.1,555.5,130.5,590.5,122.5,624,111], orient:'fixed'}},59).wait(1));

	this._renderFirstFrame();

}).prototype = p = new lib.AnMovieClip();
p.nominalBounds = new cjs.Rectangle(147.5,145.2,556.9,426.2);
// library properties:
lib.properties = {
	id: '287A2D9DF93BB5438C56D91B6E5EC74B',
	width: 550,
	height: 400,
	fps: 24,
	color: "#FFFFFF",
	opacity: 1.00,
	manifest: [
		{src:"images/жуки_HTML5 Canvas_atlas_1.png?1696618002467", id:"жуки_HTML5 Canvas_atlas_1"},
		{src:"sounds/simplyclever.mp3?1696618002492", id:"simplyclever"},
		{src:"sounds/Sound_05773.mp3?1696618002492", id:"Sound_05773"},
		{src:"sounds/zhuzhzhaniezhuka.mp3?1696618002492", id:"zhuzhzhaniezhuka"}
	],
	preloads: []
};



// bootstrap callback support:

(lib.Stage = function(canvas) {
	createjs.Stage.call(this, canvas);
}).prototype = p = new createjs.Stage();

p.setAutoPlay = function(autoPlay) {
	this.tickEnabled = autoPlay;
}
p.play = function() { this.tickEnabled = true; this.getChildAt(0).gotoAndPlay(this.getTimelinePosition()) }
p.stop = function(ms) { if(ms) this.seek(ms); this.tickEnabled = false; }
p.seek = function(ms) { this.tickEnabled = true; this.getChildAt(0).gotoAndStop(lib.properties.fps * ms / 1000); }
p.getDuration = function() { return this.getChildAt(0).totalFrames / lib.properties.fps * 1000; }

p.getTimelinePosition = function() { return this.getChildAt(0).currentFrame / lib.properties.fps * 1000; }

an.bootcompsLoaded = an.bootcompsLoaded || [];
if(!an.bootstrapListeners) {
	an.bootstrapListeners=[];
}

an.bootstrapCallback=function(fnCallback) {
	an.bootstrapListeners.push(fnCallback);
	if(an.bootcompsLoaded.length > 0) {
		for(var i=0; i<an.bootcompsLoaded.length; ++i) {
			fnCallback(an.bootcompsLoaded[i]);
		}
	}
};

an.compositions = an.compositions || {};
an.compositions['287A2D9DF93BB5438C56D91B6E5EC74B'] = {
	getStage: function() { return exportRoot.stage; },
	getLibrary: function() { return lib; },
	getSpriteSheet: function() { return ss; },
	getImages: function() { return img; }
};

an.compositionLoaded = function(id) {
	an.bootcompsLoaded.push(id);
	for(var j=0; j<an.bootstrapListeners.length; j++) {
		an.bootstrapListeners[j](id);
	}
}

an.getComposition = function(id) {
	return an.compositions[id];
}


an.makeResponsive = function(isResp, respDim, isScale, scaleType, domContainers) {		
	var lastW, lastH, lastS=1;		
	window.addEventListener('resize', resizeCanvas);		
	resizeCanvas();		
	function resizeCanvas() {			
		var w = lib.properties.width, h = lib.properties.height;			
		var iw = window.innerWidth, ih=window.innerHeight;			
		var pRatio = window.devicePixelRatio || 1, xRatio=iw/w, yRatio=ih/h, sRatio=1;			
		if(isResp) {                
			if((respDim=='width'&&lastW==iw) || (respDim=='height'&&lastH==ih)) {                    
				sRatio = lastS;                
			}				
			else if(!isScale) {					
				if(iw<w || ih<h)						
					sRatio = Math.min(xRatio, yRatio);				
			}				
			else if(scaleType==1) {					
				sRatio = Math.min(xRatio, yRatio);				
			}				
			else if(scaleType==2) {					
				sRatio = Math.max(xRatio, yRatio);				
			}			
		}			
		domContainers[0].width = w * pRatio * sRatio;			
		domContainers[0].height = h * pRatio * sRatio;			
		domContainers.forEach(function(container) {				
			container.style.width = w * sRatio + 'px';				
			container.style.height = h * sRatio + 'px';			
		});			
		stage.scaleX = pRatio*sRatio;			
		stage.scaleY = pRatio*sRatio;			
		lastW = iw; lastH = ih; lastS = sRatio;            
		stage.tickOnUpdate = false;            
		stage.update();            
		stage.tickOnUpdate = true;		
	}
}
an.handleSoundStreamOnTick = function(event) {
	if(!event.paused){
		var stageChild = stage.getChildAt(0);
		if(!stageChild.paused){
			stageChild.syncStreamSounds();
		}
	}
}


})(createjs = createjs||{}, AdobeAn = AdobeAn||{});
var createjs, AdobeAn;