Nt = require './build/Release/NtCpp'
oldNt = require '../reallyOldNt/noitech'
gen = oldNt.generate

start = new Date().getMinutes()
start *= 60
start += new Date().getSeconds()
start *= 1000
start += new Date().getMilliseconds()

Nt.sineGenerate 'dankSine0.wav', 466.667, 8820000

end = new Date().getMinutes()
end *= 60
end += new Date().getSeconds()
end *= 1000
end += new Date().getMilliseconds()

console.log 'CPP TIME IS  : ', end - start

start = new Date().getMinutes()
start *= 60
start += new Date().getSeconds()
start *= 1000
start += new Date().getMilliseconds()

voice =
  tone: 466.667
  sustain: 8820000

oldNt.buildFile 'dankSine1.wav', [gen.sine voice]

end = new Date().getMinutes()
end *= 60
end += new Date().getSeconds()
end *= 1000
end += new Date().getMilliseconds()

console.log 'COFFEE TIME IS  : ', end - start