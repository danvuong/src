function powerup(url,x,y)
{
	this.x=x;
  this.y=y;
  this.sprite = new Image();
  this.sprite.refpowerup = this;

  this.sprite.onload = function()
  {
    this.refpowerup.hauteur = this.height;
    this.refpowerup.largeur = this.width;
  }
  this.sprite.src = "js/" + url;
}


powerup.prototype.dessinerpowerup = function(contexte)
{
	contexte.drawImage(this.sprite,this.x*32,this.y*32,32,32);
}


powerup.prototype.activation = function(map)
{
	for(var i=0;i<map.powerups.length;i++)
	{
		for(var j=0;j<map.personnages.length;j++)
		{
			if(map.powerups[i].x == map.personnages[j].x && map.powerups[i].y == map.personnages[j].y)
			{
				map.powerups.splice(i,1);
				map.personnages[j].taille_explosion++;
			}
		}
	}
}

powerup.prototype.creerpowerup = function(map,contexte)
{
	map.powerups=[];
	var cases_libres = new Array();
	var temp = new Array();
	for(var i=0;i<map.collision.length;i++)
	{
		for(var j=0;j<map.collision[0].length;j++)
		{
			temp=[];
			if(map.collision[i][j]===0)
			{
				temp.push(j);
				temp.push(i);
				cases_libres.push(temp);


			}
		}
	}

	if(cases_libres.length!=0)
	{
		for(var i=0;i<10;i++){
			var random =Math.ceil(Math.random() *cases_libres.length) ;
			var pw = new powerup("power.png",0,1);
			pw.x = cases_libres[random][0];
			pw.y = cases_libres[random][1];
			map.powerups.push(pw);
	}
	}

}
