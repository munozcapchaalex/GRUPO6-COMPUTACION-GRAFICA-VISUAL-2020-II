#version 150


in vec4 color;
out vec4 color_final;

void main(void)
{ 
   
   	vec4 amarillo1= vec4(1.0f, 1.0f, 0.015f, 1.0f);
   	vec4 amarillon= vec4(0.8f, 0.8f, 0.0f, 1.0f);
   	vec4 negro =vec4(0.053f, 0.133f, 0.133f, 1.0f);
   	vec4 fondo = vec4(0.364f, 0.737f, 0.823f,1.0f);
   	vec4 rojoClaro= vec4(0.768f, 0.191f, 0.191f, 1.0f);
   	vec4 rojoOscuro= vec4(0.693f, 0.133f, 0.133f, 1.0f);
    vec4 blanco= vec4(1.0f, 1.0f, 1.0f, 1.0f);			
	vec4 gris = vec4(0.294f,0.4f,0.439f,1.0f);
	vec4 morado = vec4(0.419f,0.188f,0.737f,1.0f);
	vec4 celeste = vec4(0.588f,0.792f,0.862f,1.0f);
 //CARA///////////////////////////////////////////////////////////////////////////////////////////////////////////
  	float centroy = gl_FragCoord.y -600;
  	float centrox =gl_FragCoord.x -600;
  	float x = centrox;
  	float xcuad = x*x;
    float y = centroy;
  	float ycuad = y*y;	
  	float suma = xcuad + ycuad;	
  	//basecara	 
   	if(suma <10000){ // radio 100
  		color_final = amarillo1;
  	}
  	else if(suma> 10000 && suma<10609){ //radio 100 - 103
  		color_final = negro;
  	}else{
  		color_final = fondo;
   	}   
  //boca
   y = centroy ;
   x = centrox;
   xcuad = x*x;
   ycuad = y*y;
   suma = xcuad + ycuad;
  
  	if(suma> 2500 && suma<2800){
  		color_final = negro;
  	}
  y = centroy;
  x = centrox;
   	if(y <80 &&  y > -35 ){ // radio 10
  		if (x<60 && x>-60) {color_final = amarillo1;}
  	}
  		
   	//OJOI 
   y = centroy-30;
   x = centrox+30;
   xcuad = x*x;
   ycuad = y*y;
   suma = xcuad + ycuad;
 
   	if(suma <100){ // radio 10
  		color_final = morado;
  	}
  	else if(suma> 100 && suma<180){ //radio 100 - 103
  		color_final = negro;
   	} 
   	//OJOD
   y = centroy-30;
   x = centrox-30;
   xcuad = x*x;
   ycuad = y*y;
   suma = xcuad + ycuad;
  
    	if(suma <100){ // radio 10
  		color_final = amarillon;
  	}
  	else if(suma> 100 && suma<180){ //radio 100 - 103
  		color_final = negro;
   	} 
//RATÓN//////////////////////////////////////////////////////////////////////////////////////////////////////

   	float centroyR = gl_FragCoord.y -550;
  	float centroxR =gl_FragCoord.x -200;
  	
  	 
   //2da parte
   y = centroyR -150;
   x = centroxR;
   xcuad = x*x;
   ycuad = y*y;
   suma = xcuad + ycuad;
   
   if(suma < 2500){
   		color_final = rojoOscuro;
   }else if(suma> 2500 && suma<3025){ //radio 50 y 55
  		color_final = negro;

   }
   
   //3ra parte 
   
   y = centroyR -200;
   x = centroxR-50;
   ycuad = y*y;
   xcuad = x*x;
   suma = xcuad + ycuad;
   
      if(suma < 400){
   		color_final = rojoOscuro;
   }else if(suma>400  && suma<625){ //radio 20 y 25
  		color_final = negro;
   }
   
   
   y = centroyR -200;
   x = centroxR +50;
   ycuad = y*y;
   xcuad = x*x;
   suma = xcuad + ycuad;
   
      if(suma < 400){
   		color_final = rojoOscuro;
   }else if(suma>400  && suma<625){ //radio 20 y 25
  		color_final = negro;
   } 
   
   
   y = centroyR ;
   x = centroxR -100;
   ycuad = y*y;
   xcuad = x*x;
   suma = xcuad + ycuad;
   
      if((suma < 4900)){
   		color_final = fondo;
   }else if(suma>4900 && suma< 5625){ //radio 90 y 95
  		color_final = negro;
  	}
  	
   y = centroyR ;
   x = centroxR;
   ycuad = y*y;
   xcuad = x*x;
   suma = xcuad + ycuad;
   
      if((suma < 8100)){
   		color_final = rojoOscuro;
   }else if(suma> 8100 && suma<9025){ //radio 90 y 95
  		color_final = negro;
  	}

   y = centroyR-68;
   x = centroxR-150;
   ycuad = y*y;  
   xcuad = x*x;
   suma = xcuad + ycuad;
   
      if((suma < 4900)){
   		color_final = fondo;
   }
   
   y = centroyR-90;
   x = centroxR-89;
   ycuad = y*y;  
   xcuad = x*x;
   suma = xcuad + ycuad;
      if((suma < 1000)){
   		color_final = fondo;
   }
  //FIGURA LIBRE A//////////////////////////////////////////////////////////////////////////////////////////////////
     //AMONG US
   float centrox3=gl_FragCoord.x-200;
   float centroy3=gl_FragCoord.y-200;
   //cabeza
   y=centroy3-50;
   x=centrox3;
   xcuad=x*x;
   ycuad=y*y;
   suma=xcuad+ycuad;
   if(suma<2360){
   		color_final=rojoOscuro;
   }else if(suma>2360 && suma< 3000){ //radio 90 y 95
  		color_final = negro;
  	}
  	//contorno mochila
   x=centrox3+50;
   y=centroy3;
   if(y>-55 && y<55 && x<15 && x>-25){
   		color_final=negro;
   }
   //mochila
   x=centrox3+50;
   y=centroy3;
   if(y>-50 && y<50 && x<20 && x>-20){
   		color_final=morado;
   }
   //contorno patas
   x=centrox3+30;
   y=centroy3+70;
   if(y>-30 && y<55 && x<25 && x>-25){
   		color_final=negro;
   }
   x=centrox3-30;
   if(y>-30 && y<55 && x<25 && x>-25){
   		color_final=negro;
   }
   //contorno cuerpo
   x=centrox3;
   y=centroy3+50;
   if(y>-25 && y<105 && x<55 && x>-55){
   		color_final=negro;
   }
   
   //cuerpo
   x=centrox3;
   y=centroy3+50;
   if(y>-20 && y<100 && x<50 && x>-50){
   		color_final=morado;
   }
   y=centroy3-50;
   x=centrox3;
   xcuad=x*x;
   ycuad=y*y;
   suma=xcuad+ycuad;
   if(suma<2360){
   		color_final=morado;
   }
   //patas
   x=centrox3+30;
   y=centroy3+70;
   if(y>-25 && y<50 && x<20 && x>-20){
   		color_final=morado;
   }
   x=centrox3-30;
   if(y>-25 && y<50 && x<20 && x>-20){
   		color_final=morado;
   }
   //ojo contorno
   y=centroy3-50;
   x=centrox3-35;
   xcuad=x*x;
   ycuad=y*y;
   suma=xcuad+ycuad;
   if(suma>500 && suma<800){ //radio 90 y 95
  		color_final = negro;
   }
   y=centroy3-50;
   x=centrox3-6;
   xcuad=x*x;
   ycuad=y*y;
   suma=xcuad+ycuad;
   if(suma>500 && suma<800){ //radio 90 y 95
  		color_final = negro;
  }
  y=centroy3-50;
  x=centrox3-17.5;
  if(y>-28 && y<28 && x<20 && x>-20){
   		color_final=negro;
  }
  //ojo color
   y=centroy3-50;
   x=centrox3-35;
   xcuad=x*x;
   ycuad=y*y;
   suma=xcuad+ycuad;
   if(suma<500){ //radio 90 y 95
  		color_final =gris;
   }
   y=centroy3-50;
   x=centrox3-6;
   xcuad=x*x;
   ycuad=y*y;
   suma=xcuad+ycuad;
   if(suma<500){ //radio 90 y 95
  		color_final =gris;
  }
  y=centroy3-50;
  x=centrox3-17.5;
  if(y>-22 && y<22 && x<20 && x>-20){
   		color_final=gris;
  }
   //ojo sombra1
   y=centroy3-55;
   x=centrox3-40;
   xcuad=x*x;
   ycuad=y*y;
   suma=xcuad+ycuad;
   if(suma<300){ //radio 90 y 95
  		color_final =celeste;
   }
   y=centroy3-55;
   x=centrox3-10;
   xcuad=x*x;
   ycuad=y*y;
   suma=xcuad+ycuad;
   if(suma<300){ //radio 90 y 95
  		color_final =celeste;
  }
  y=centroy3-55;
  x=centrox3-25;
  if(y>-17 && y<17 && x<18 && x>-18){
   		color_final=celeste;
  } 
  //FUGURA LIBRE B//////////////////////////////////////////////////////////////////////////////////////////////////
  

   	centroy = gl_FragCoord.y -200;
    centrox = gl_FragCoord.x -600;

  	vec4 amarillo = vec4(0.929f, 0.721f, 0.474f,1.0f);
   	float x1 = centrox;
  	float xcuad1 = x1*x1;
    float y1 = centroy;
  	float ycuad1 = y1*y1;		
  	float suma1 = xcuad1 + ycuad1;
  	
  	
   //panza
   y1 = centroy+50;
   x1 = centrox;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 8100){
   		color_final = rojoOscuro;
   }
    
    //panza pequeña
   y1 = centroy+35;
   x1 = centrox;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 5329){
   		color_final = amarillo;
   }
   
   //cabeza
   
   y1 = centroy-90;
   x1 = centrox;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 2500){
   		color_final = rojoOscuro;
   }
   
   //hocico
   
   y1 = centroy-68;
   x1 = centrox;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 729){
   		color_final = amarillo;
   }
   
   //nariz
   
   y1 = centroy-84;
   x1 = centrox;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   if(suma1 < 150){
   		color_final = rojoOscuro;
   }  
   
   //ojos grande
   
   y1 = centroy-100;
   x1 = centrox-30;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 60){
   		color_final = negro;
   }  
   
   //ojos grande
   
   y1 = centroy-100;
   x1 = centrox+30;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 60){
   		color_final = negro;
   }
   
   //ojito
   
   y1 = centroy-100;
   x1 = centrox-30;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 10){
   		color_final = fondo;
   }
   
   //ojito
   
   y1 = centroy-100;
   x1 = centrox+30;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 10){
   		color_final = fondo;
   }
   
   //orejas
   
   y1 = centroy-145;
   x1 = centrox-50;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 625){
   		color_final = rojoOscuro;
   }
   
   y1 = centroy-145;
   x1 = centrox+50;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 625){
   		color_final = rojoOscuro;
   }
   
   y1 = centroy-140;
   x1 = centrox+50;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 289){
   		color_final = amarillo;
   }
   
   y1 = centroy-140;
   x1 = centrox-50;
   xcuad1 = x1*x1;
   ycuad1 = y1*y1;
   suma1 = xcuad1 + ycuad1;
   
   if(suma1 < 289){
   		color_final = amarillo;
   }



	// vec4 posA = vec4(centrox, centroy, 0.0f, 1.0f);
	//	x = 0.1*posA.x+1.5;
	//  y = 0.1*posA.y+10;
	
	   //if((x >1.5*y-4)&&(x < 0)&&(-x<1.5*y+4)){
   		//color_final = negro;
  	 //}
  	 
  	 //patas
  	 
	y1 = centroy;
    x1 = centrox+50;
	x = 0.04*x1+3.3;
	y = 0.04*y1-1;

   if((x >y)&&(x< y+3)&&(x > -y)&&(x<-y+3)){
   	color_final = rojoOscuro;
   }
   
   	 y1 = centroy;
     x1 = centrox+50;
	x = 0.04*x1-4.3;
	y = 0.04*y1-1;
	
      if((x >y)&&(x< y+3)&&(x > -y)&&(x<-y+3)){
   	color_final = rojoOscuro;
   }
   
   
   	y1 = centroy;
    x1 = centrox+50;
	x = 0.04*x1+3.3;
	y = 0.04*y1+5;

   if((x >y)&&(x< y+3)&&(x > -y)&&(x<-y+3)){
   	color_final = rojoOscuro;
   }
   
   	 y1 = centroy;
     x1 = centrox+50;
	x = 0.04*x1-4.3;
	y = 0.04*y1+5;
	
      if((x >y)&&(x< y+3)&&(x > -y)&&(x<-y+3)){
   	color_final = rojoOscuro;
   }
  //EJES DE COORDENADAS/////////////////////////////////////////////////////////////////////////////////////////////
 	float centroyCD = gl_FragCoord.y -400;
  	float centroxCD =gl_FragCoord.x -400;
 	y = centroyCD ;
   	x = centroxCD;

   	if(y<2 &&  y>-2 ){ // radio 10
  		color_final = blanco;
  	}  
	if(x<2 &&  x>-2 ){ // radio 10
  		color_final = blanco;
  	}
}