var mp = new map(tab_map);
var aff_menu = new map(map_menu);
var joueur = new personnage("endive.png",0,6,DIRECTION.BAS);
var joueur2 = new personnage("patate.png",14,6,DIRECTION.BAS);
var image_menu = new Image();
image_menu.src = "js/menu.png";

var mur_map = new Array();
mur_map =
[[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1],
[0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],
[0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],
[0,1,0,1,0,0,0,0,0,1,0,0,0,1,0],
[0,0,1,0,1,0,1,0,1,0,1,0,1,0,0],
[0,1,0,1,0,0,0,0,0,1,0,0,0,1,0],
[1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],
[0,0,0,1,0,0,0,0,0,1,0,0,0,0,0],
[1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],
[0,0,0,1,0,0,0,0,0,0,0,0,0,0,0],
[1,0,1,0,1,0,1,0,1,0,1,0,1,0,1],
[0,0,0,1,0,0,0,0,0,1,0,0,0,0,0],
[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]];

var mur_map_incassable = new Array();
mur_map_incassable =
[[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,0,1,0,1,0,1,0,1,0,1,0,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]


function explose(map,bombe,numero_joueur)
	{
		switch(numero_joueur)
		{
			case 1 : 
			var ex = new sprite("explosion.png",5,6);
			map.bombes1.splice(map.bombes1.indexOf(bombe),1); 
 			ex.coord_explosion(map,bombe,1);
 			setTimeout(function(){duree_explosion(map,ex,numero_joueur)},500);
			break;
			case 2 :
			var ex2 = new sprite("explosion.png",5,6);
			map.bombes2.splice(map.bombes2.indexOf(bombe),1);
			ex2.coord_explosion(map,bombe,2);
			setTimeout(function(){duree_explosion(map,ex2,numero_joueur)},500);
			break;
		}

	} 

function duree_explosion(map,explosion,joueur)
{
	switch(joueur)
	{
		case 1:
		for(var i=0;i<map.explosions.length;i++)
		{
		if(map.explosions[i].indexOf(explosion) !== -1)
		{
		map.explosions.splice(i,1);
		}
		}
		break;
		case 2:
		for(var i=0;i<map.explosions2.length;i++)
		{
		if(map.explosions2[i].indexOf(explosion) !== -1)
		{
		map.explosions2.splice(i,1);
		}
		}		break;
	}
}


joueur.nombre_bombe=3;
joueur2.nombre_bombe=3;
mp.addpersonnage(joueur);
mp.addpersonnage(joueur2);


window.onload = function() {

	var canvas = document.getElementById('canvas');
	var ctx = canvas.getContext('2d');
	
	var power = new powerup("power.png",0,1)


	for( var i =0;i<mur_map.length; i++){
      for(var j=0;j<mur_map[0].length;j++){
        var mr = new mur("mur.png",5,6);
        mr.x = j;
        mr.y = i;
        if(mur_map[i][j]==0)
        {
          mr.etat=0;
        };
       mp.murs.push(mr);
      }
    };


for( var i =0;i<mur_map_incassable.length; i++){
      for(var j=0;j<mur_map_incassable[0].length;j++){
        var mr = new mur("mur_incassable.png",5,6);
        mr.x = j;
        mr.y = i;
        if(mur_map_incassable[i][j]==0)
        {
          mr.etat=0;
        };
       mp.murs_incassable.push(mr);
      }
    };


 var test_mur = function()
{
  	for(var i=0;i<mp.murs.length;i++)
  	{
  		mp.murs[i].casse_mur(mp);
  	}
 }

 var gameover = function(joueur)
 {
  	document.write("<B>GAME OVER</B>"+ "<B> Le joueur </B>" + joueur+"<B> a gagné!</B>");
  	
  	window.onkeydown = function(event) {
	var e = event || window.event;
	var key = e.which || e.keyCode;
	if(key == 13)
	{
		menu();
	};
	}
 };

var jeu = function(){
	

	id = setInterval(function() {

		test_mur();
		if(joueur.mort(mp))
			{
				clearInterval(id);
				gameover("patate");
			};
			if(joueur2.mort(mp))
			{
				clearInterval(id);
				gameover("endive");
			};

		mp.addcollision();
		power.activation(mp);
		mp.dessinermap(ctx);


		

	}, 20);

	setTimeout(function(){
	 power.creerpowerup(mp,ctx);
	},100)



	var keymap = new Array();
	var interval = null;
	onkeydown = function(e){
    e = e || event; // to deal with IE
    keymap[e.keyCode] = true;

    if(interval === null){
    id2 = setInterval(function(){
		if(keymap[122] || keymap[90] || keymap[87])		
		{
			joueur.deplacer(DIRECTION.HAUT,mp);
			// return true;
		}
		if(keymap[38])
		{
			joueur2.deplacer(DIRECTION.HAUT,mp);
			// return true;
		}
		if(keymap[115] || keymap[83] )
		{
			joueur.deplacer(DIRECTION.BAS,mp);
			// return true;
		}	
		if(keymap[40])
		{
			joueur2.deplacer(DIRECTION.BAS,mp);
			// return true;
		}
		if(keymap[113]||keymap[97]||keymap[81]||keymap[65])
		{
			joueur.deplacer(DIRECTION.GAUCHE,mp);
			// return true;
		}
		if(keymap[37])
		{
			joueur2.deplacer(DIRECTION.GAUCHE,mp);
			// return true;
		}
		if(keymap[100]||keymap[68])
		{
			joueur.deplacer(DIRECTION.DROITE,mp);
			// return true;
		}
		if(keymap[39])
		{
			joueur2.deplacer(DIRECTION.DROITE,mp);
			// return true;
		}
		
		else
		{	// 		//alert(key);
			// Si la touche ne nous sert pas, nous n'avons aucune raison de bloquer son comportement normal.
			return true;
		}
	},1000/50);}
	if(keymap[32])
		{
			if(mp.bombes1.length<joueur.nombre_bombe)
			{
			var bm = new bombe("bombe.png",1,5);

			bm.poserbombe(joueur.x,joueur.y)
			mp.addbombe(bm,1);
			window.setTimeout(function(){explose(mp,bm,1)},2000);
			// return true;
			}
		}
		if(keymap[96])
		{
			if(mp.bombes2.length<joueur2.nombre_bombe)
			{

			var bm2 = new bombe("bombe.png",1,7);


			bm2.poserbombe(joueur2.x,joueur2.y)
			mp.addbombe(bm2,2);
			window.setTimeout(function(){explose(mp,bm2,2)},2000);			
			// return true;

			}
		}

}
onkeyup = function(e)
{
	e = e || event; // to deal with IE
    keymap[e.keyCode] = false;
    clearInterval(id2);
    interval=null;
}


}



var menu = function(){
	aff_menu.dessinermap(ctx);
	ctx.drawImage
	(image_menu,0,0,aff_menu.largeur*32,aff_menu.height*32);




};


menu();

window.onkeydown = function(event) {
var e = event || window.event;
var key = e.which || e.keyCode;
switch(key){
	case 13:
	jeu();
	break;
}
}





}
