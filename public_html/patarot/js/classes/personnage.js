var DIRECTION = {
	"BAS"    : 0,
	"GAUCHE" : 1,
	"DROITE" : 2,
	"HAUT"   : 3
}

var DUREE_ANIMATION = 4;
var DUREE_DEPLACEMENT = 10;

function personnage(url,x,y,direction){
  this.sprite = new Image();
  this.x = x;
  this.y = y;
  this.etat =1;
  this.nombre_bombe;
  this.taille_explosion=1;
  this.sprite.refperso =this;
  this.etatAnimation = -1;
	this.direction = direction;


  this.sprite.onload = function(){
    this.refperso.largeur = this.width;
    this.refperso.hauteur = this.height;
  }
  this.sprite.src ="js/" + url;
}

  personnage.prototype.dessinerpersonnage = function(contexte){
		var decalageX =0;
		var decalageY = 0;

    if(this.etatAnimation >= DUREE_DEPLACEMENT) {
		this.etatAnimation = -1;
  }
	if(this.etatAnimation >=0){
    var pixelsAParcourir = 32 - (32 * (this.etatAnimation / DUREE_DEPLACEMENT));

    if(this.direction == DIRECTION.HAUT) {
			decalageY = pixelsAParcourir;
		} else if(this.direction == DIRECTION.BAS) {
			decalageY = -pixelsAParcourir;
		} else if(this.direction == DIRECTION.GAUCHE) {
			decalageX = pixelsAParcourir;
		} else if(this.direction == DIRECTION.DROITE) {
			decalageX = -pixelsAParcourir;
		}
		this.etatAnimation++;
	}

	if(this.etat == 1)
		{
		contexte.drawImage(this.sprite,0,0,this.largeur,this.hauteur,this.x*32+decalageX,this.y*32+decalageY,32,32)
		};
  }

personnage.prototype.getCoordonneesAdjacentes = function(direction){
  var coord = {'x' : this.x, 'y' : this.y};
  switch(direction){
    case DIRECTION.BAS :
			coord.y++;
			break;
		case DIRECTION.GAUCHE :
			coord.x--;
			break;
		case DIRECTION.DROITE :
			coord.x++;
			break;
		case DIRECTION.HAUT :
			coord.y--;
			break;
	}
	return coord;
}

personnage.prototype.mort = function(map)
{
		for(var j=0;j<map.explosions.length;j++)
		{
			for(var k =0;k<map.explosions[j].length;k++)
			{

				if((map.explosions[j][k].x == this.x) && (map.explosions[j][k].y == this.y))
				{
					this.etat =0;
					return true;
				}
			}
		}
		for(var j=0;j<map.explosions2.length;j++)
		{
			for(var k =0;k<map.explosions2[j].length;k++)
			{

				if((map.explosions2[j][k].x == this.x) && (map.explosions2[j][k].y == this.y))
				{
					this.etat =0;
					return true;
				}
			}
		}
}

personnage.prototype.deplacer = function(direction,map){
	if(this.etatAnimation >=0){
		return false;
	}
	this.direction = direction;
  var prochaineCase = this.getCoordonneesAdjacentes(direction);
	if(prochaineCase.x<0 || prochaineCase.y<0||prochaineCase.x>map.largeur-1||prochaineCase.y>map.height-1||map.collision[prochaineCase.y][prochaineCase.x]==1){
		return false;
	};

  this.etatAnimation =1;
  this.x = prochaineCase.x;
  this.y = prochaineCase.y;
}
