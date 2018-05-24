var ts = new Tileset("basique.png");


var mp = new map(tab_map);
var aff_menu = new map(map_menu);
var joueur = new personnage("endive.png",0,1,DIRECTION.BAS);
var joueur2 = new personnage("patate.png",4,1,DIRECTION.BAS);
var etat=0;

mp.addpersonnage(joueur);
mp.addpersonnage(joueur2);



window.onload = function() {
	var canvas = document.getElementById('canvas');
	var ctx = canvas.getContext('2d');


menu = function(etat){
	this.etat = etat;
switch(this.etat){

	case 1:

	setInterval(function() {
		mp.dessinermap(ctx);
	}, 40);


	window.onkeydown = function(event) {
	var e = event || window.event;
	var key = e.which || e.keyCode;

	switch(key) {
		case 122 : case 119 : case 90 : case 87 : // Flèche haut, z, w, Z, W
			joueur.deplacer(DIRECTION.HAUT,mp);
			break;
		case  38 :
			joueur2.deplacer(DIRECTION.HAUT,mp);
			break;
		case 115 : case 83 : // Flèche bas, s, S
			joueur.deplacer(DIRECTION.BAS,mp);
			break;
		case  40:
			joueur2.deplacer(DIRECTION.BAS,mp);
			break;
		case 113 : case 97 : case 81 : case 65 : // Flèche gauche, q, a, Q, A
			joueur.deplacer(DIRECTION.GAUCHE,mp);
			break;
		case  37:
			joueur2.deplacer(DIRECTION.GAUCHE,mp);
			break;
		case 100 : case 68 : // Flèche droite, d, D
			joueur.deplacer(DIRECTION.DROITE,mp);
			break;
		case  39 :
			joueur2.deplacer(DIRECTION.DROITE,mp);
			break;
		default :
			//alert(key);
			// Si la touche ne nous sert pas, nous n'avons aucune raison de bloquer son comportement normal.
			return true;
	}

	return false;
}
break;

case 0:


	aff_menu.dessinermap(ctx);


window.onkeydown = function(event) {
var e = event || window.event;
var key = e.which || e.keyCode;
switch(key){
	case 38:
	this.etat = 1;
	alert('ok');

	continue loop1;
	break;
}
}

break;


}



}

loop1:
	menu(etat);











}
