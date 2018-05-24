var taille_map = 15;



var tab_map = new Array();
for(var i = 0;i<taille_map;i++){
  var temp = new Array();
  for(var j =0;j<taille_map;j++){
    temp.push(2);
  }
  tab_map.push(temp);
}
;


 

var map_menu = new Array();
for(var i=0; i<taille_map;i++){
  var temp = new Array();
  for(var j=0; j<taille_map;j++){
    temp.push(1);

  }
  map_menu.push(temp);
}

function map(choix){
  this.choix=choix;
  this.height = choix.length;
  this.largeur = choix[0].length;
  this.tileset=new Tileset("basique.png");
  this.bombes1 = new Array();
  this.bombes2 = new Array();
  this.personnages = new Array();
  this.collision = new Array();
  this.explosions= new Array();
  this.explosions2= new Array();
  this.powerups = new Array();
  this.murs=new Array();
  this.murs_incassable = new Array();



}

map.prototype.addpersonnage = function(perso)
{
  this.personnages.push(perso);
}

map.prototype.addexplosion = function(explosion,joueur)
{
  switch(joueur)
  {
  case 1 :
  this.explosions.push(explosion);
  break;
  case 2 :
  this.explosions2.push(explosion);
  break;

  }
}


map.prototype.addbombe = function(bombe,joueur)
{
  switch(joueur)
  {
    case 1: 
    this.bombes1.push(bombe);
    break;
    case 2 : this.bombes2.push(bombe);
    break;
  }
}

map.prototype.addpowerup = function(powerup)
{
  this.powerups.push(powerup);
}

map.prototype.addcollision = function()
{
  this.collision=[];
  for(var i=0; i<this.height;i++){
    var temp = new Array();
    for(var j=0; j<this.largeur;j++){
      temp.push(0);

    }
    this.collision.push(temp);
  }
      for(var i =0; i<this.murs.length;i++)
      {
        if(this.murs[i].etat==1)
        {
        this.collision[this.murs[i].y][this.murs[i].x]=1;
        }
      }
       for(var i =0; i<this.murs_incassable.length;i++)
      {
        if(this.murs_incassable[i].etat==1)
        {
        this.collision[this.murs_incassable[i].y][this.murs_incassable[i].x]=1;
        }
      }
      for(var i =0; i<this.bombes1.length;i++)
      {
  
        this.collision[this.bombes1[i].y][this.bombes1[i].x]=1;
      }
      for(var i =0; i<this.bombes2.length;i++)
      {
        this.collision[this.bombes2[i].y][this.bombes2[i].x]=1;
      }
}


  // map.prototype.mur_stop = function()
  // {
  //    for(var i=0;i<this.explosions.length;i++)
  //    {
  //    for(var j=0;j<this.explosions[0].length;j++)
  //     {
  //       for(var k=0;k<this.murs_incassable.length;k++){
  //         if(this.explosions[i][j].x == this.murs_incassable[k].x && this.explosions[i][j].y == this.murs_incassable[k].y)
  //          {
  //           this.explosions[i].splice(j,1);
  //         }
  //      }
  //     }
  //   }
  // }

  map.prototype.dessinermap = function(contexte){


    for( var i =0, l=this.height;i<l; i++){
      for(var j=0, k = this.largeur;j<l;j++){
        this.tileset.dessinerTile(this.choix[i][j],contexte,j*32,i*32);
      }
    };


   

    for(var i =0; i<this.murs.length;i++)
    {
      this.murs[i].dessinermur(contexte);
    }

    for(var i =0; i<this.murs_incassable.length;i++)
    {
      this.murs_incassable[i].dessinermur(contexte);
    }



    for(var i = 0, l=this.bombes1.length; i<l;i++){
      this.bombes1[i].dessinerbombe(contexte);
    }
    for(var i = 0, l=this.bombes2.length; i<l;i++){
      this.bombes2[i].dessinerbombe(contexte);
    }

    for(var i=0;i<this.powerups.length;i++)
    {
      this.powerups[i].dessinerpowerup(contexte);
    }

    for(var j = 0;j<this.explosions.length;j++)
    {
      for(var i=0;i<this.explosions[0].length;i++)
      this.explosions[j][i].dessinersprite(contexte);
    }

    for(var i = 0;i< this.explosions2.length;i++)
    {
      for(var j=0;j<this.explosions2[0].length;j++)
      {
      this.explosions2[i][j].dessinersprite(contexte);
      }
    }


    for(var i = 0, l=this.personnages.length; i<l;i++){
      this.personnages[i].dessinerpersonnage(contexte);
    }
  }
