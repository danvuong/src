


function bombe(url,x,y)
{
  this.x=x;
  this.y=y;
  this.sprite = new Image();
  this.sprite.refbombe = this;
  this.timer=0;

  this.sprite.onload = function()
  {
    this.refbombe.hauteur = this.height;
    this.refbombe.largeur = this.width;
  }
  this.sprite.src = "js/" + url;

}


bombe.prototype.poserbombe = function(x,y)
{
   this.x = x;
   this.y =y;
}



bombe.prototype.dessinerbombe = function(contexte)
{

  if(this.timer!=100)
  {
  contexte.drawImage(this.sprite,this.x*32,this.y*32,32,32);
  }
};
