var smiley = new Image();
smiley.src = "D:/Projet_patarot/js/endive.png";



window.onload = function() {
	var canvas = document.getElementById('canvas');
	var ctx = canvas.getContext('2d');

	//ctx.fillStyle = 'blue';
	//ctx.fillRect(10, 10, 100, 50);

	//ctx.strokeStyle = 'red';
	//ctx.strokeRect(75, 75, 50, 50);

  ctx.drawImage(smiley, 200, 10);
	ctx.drawImage(smiley, 200, 30, 100, 50);
	ctx.drawImage(smiley, 300, 30, 200, 50);
	ctx.drawImage(smiley, 200, 100, 50, 50);
	ctx.drawImage(smiley, 100, 30, 100, 50);


}
