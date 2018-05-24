

function sprite(url,x,y)
{
	this.x=x;
	this.y=y;
	this.numero=0;
	this.image = new Image();
	this.image.refsprite = this;	
	
	this.image.onload = function()
  {
    this.refsprite.hauteur = this.height;
    this.refsprite.largeur = this.width;
  }
  this.image.src = "js/" + url;
}

sprite.prototype.coord_explosion = function(map,bombe,joueur)
{
	
	var temp  = new Array();
	this.x = bombe.x+1;
	this.y= bombe.y;
	temp.push(this)
	var explo = new sprite("explosion.png",2,4)
	explo.x = bombe.x-1;
	explo.y= bombe.y;
	temp.push(explo);
	var explo = new sprite("explosion.png",2,4)
	explo.x = bombe.x;
	explo.y= bombe.y+1;
	temp.push(explo);
	var explo = new sprite("explosion.png",2,4)
	explo.x = bombe.x;
	explo.y= bombe.y-1;
	temp.push(explo);

	
	for(var i=1;i<map.personnages[joueur-1].taille_explosion+1;i++)
	{
		var explo = new sprite("explosion.png",2,4)

	explo.x = bombe.x+i;
	explo.y= bombe.y;
	temp.push(explo)
	var explo = new sprite("explosion.png",2,4)
	explo.x = bombe.x-i;
	explo.y= bombe.y;
	temp.push(explo);
	var explo = new sprite("explosion.png",2,4)
	explo.x = bombe.x;
	explo.y= bombe.y+i;
	temp.push(explo);
	var explo = new sprite("explosion.png",2,4)
	explo.x = bombe.x;
	explo.y= bombe.y-i;
	temp.push(explo);
	}



	map.addexplosion(temp,joueur);
	

  
}


sprite.prototype.dessinersprite = function(contexte)
{
  contexte.drawImage(this.image,this.x*32,this.y*32,32,32);
  
};