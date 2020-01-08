var fs = require("fs");

// help turn lua script into string to inject into lua with c
// use: node stringit.js ssl.lua | pbcopy

if (process.argv.length === 2) {
	console.error('Expected at least one argument!');
	process.exit(1);
}

let file = process.argv[2];

fs.readFile(file, function(err, data) {
	if (!err) {
		var original = data.toString();
		original = original.replace(/\"/g, "\\\"");
		original = original.replace(/\n/g, "\\n\n");
		original = original.replace(/[^\r\n]+/g, '"$&"');
		var newString = original;
		console.log(newString)
	} else {
		console.log('error');
	}
});