module servo(){

    A = 32;
    B = 23;
    C = 29;
    D = 13;
    E = 32;
    F = 18;
    motorHoleSize = 2.5;

    union(){
         
        color([0.1,0.5,0.8,1])
        difference(){
            
            union(){

                cube([B, D, B]);
                translate([B,0,F-2]) cube([(E-B)/2,D,2]);
                translate([-(E-B)/2,0,F-2]) cube([(E-B)/2,D,2]);
                translate([7,D/2,C-6]) cylinder(h=A-C,r=D/2);
                translate([13,D/2,C-6]) cylinder(h=A-C,r=3);
                
            };
                
            translate([E-5.5,D/2,10]) cylinder(r=motorHoleSize,h=10);
            translate([-3.5,D/2,10]) cylinder(r=motorHoleSize,h=10);
            
        };
        
        color([0.9,0.9,0.9,1]) translate([7,D/2,A-6]) cylinder(h=A-C,r=3);
        
        color([1,1,1,1]) translate([-6,3,29]) cube([B+3,6,2]);
        
    };

};

module servoMountFixed(){

    shift = 0.5;
    innerWidth = 24;
    innerDepth = 14;
    wingWidth = 7;
    wingThickness = 4;
    sideThickness = 2;
    sideHeight = 10;
    height = 14;
    holeSize = 2.5;
    holeSizeLarge = 4;
    bottomWidth = 1.0;
    bottomHeight= 10.5;
    outerWidth = innerWidth+2*wingWidth;
    outerWidthLower = outerWidth*bottomWidth;
    
    translate([-shift,-shift,-wingThickness/2])
    difference(){
        
        difference(){
            
            union(){
                
                translate([-wingWidth, 0, height]) 
                cube([wingWidth, innerDepth, wingThickness]);
                translate([innerWidth, 0, height]) 
                cube([wingWidth, innerDepth, wingThickness]);

                translate([-wingWidth, -sideThickness, height-sideHeight+wingThickness]) 
                cube([outerWidth, sideThickness, sideHeight]);
                translate([outerWidth/2-wingWidth - outerWidthLower/2, -sideThickness, height-sideHeight-bottomHeight+wingThickness]) 
                cube([outerWidthLower, sideThickness, bottomHeight]);
                
                translate([-wingWidth, innerDepth, height-sideHeight+wingThickness]) 
                cube([outerWidth, sideThickness, sideHeight]);
                translate([outerWidth/2-wingWidth - outerWidthLower/2, innerDepth, height-sideHeight-bottomHeight+wingThickness]) 
                cube([outerWidthLower, sideThickness, bottomHeight]);
                
                translate([outerWidth/2-wingWidth - outerWidthLower/2, -sideThickness+sideThickness, height-sideHeight-bottomHeight+wingThickness]) 
                cube([outerWidthLower, innerDepth, wingThickness]);
                
            }
            
            translate([-wingWidth/2,innerDepth/2,height-5]) cylinder(r=holeSize,h=10);
            translate([-wingWidth/2-wingWidth+outerWidth,innerDepth/2,height-5]) cylinder(r=holeSize,h=10);
            
        }
        
        translate([-wingWidth/2,innerDepth*1.5,height-(bottomHeight+sideHeight)/2+holeSize/2+wingThickness/2]) rotate([90,0,0]) cylinder(r=holeSize,h=2*innerDepth);
        translate([innerWidth+wingWidth/2-holeSize/2,innerDepth*1.5,height-(bottomHeight+sideHeight)/2+holeSize/2+wingThickness/2]) rotate([90,0,0]) cylinder(r=holeSize,h=2*innerDepth);
        translate([7,6.5,-10]) cylinder(r=holeSize,h=2*innerDepth);
        translate([7,6.5,-1]) cylinder(r=holeSizeLarge,h=10);
        
    }
    
};
module servoConnectStraight(){
    
    armLength = 50;
    connectorLength = 90;
    armThickness = 4;
    armWidth = 28;
    innerHeight = 41;
    holeSize = 1.5;
    holeFromEdge = 13;
    holesEvery = 5;
    holeFromEdgeBot = 23;
    holeSizeBot = 2.5;
    connectorHeight = 16;
    connectorVertOffset = 3;
    
    translate([-armLength+30,+6-armWidth/2,-innerHeight/2+11])  difference(){
        
        color("red") union(){
            
            translate([0,0,0]) cube([armLength, armWidth, armThickness]);
            translate([0,0,innerHeight]) cube([armLength, armWidth, armThickness]);
            translate([-armThickness,0,0]) cube([armThickness, armWidth, innerHeight+armThickness]);
            
            // Conectors
            translate([-armThickness-connectorLength,0,armThickness+connectorVertOffset]) cube([connectorLength, armThickness, connectorHeight]);
            translate([-armThickness-connectorLength,armWidth-armThickness,armThickness+connectorVertOffset]) cube([connectorLength, armThickness, connectorHeight]);
            
            // Support in center of connector
            translate([-connectorLength/3,armThickness,armThickness+connectorVertOffset]) cube([armThickness, armWidth-2*armThickness, connectorHeight]);
            
            
        }
        
        for (i = [0:4]){
            translate([armLength-i*holesEvery-holeFromEdge,armWidth/2,innerHeight]) cylinder(r=holeSize,h=20,center=true);
        }
        translate([armLength-holeFromEdgeBot,armWidth/2,0]) cylinder(r=holeSizeBot,h=20,center=true);
        translate([-connectorLength+6,armWidth/2,armThickness+connectorHeight/2+connectorVertOffset]) rotate([90,0,0]) cylinder(r=holeSizeBot,h=40,center=true);
        translate([-connectorLength+36,armWidth/2,armThickness+connectorHeight/2+connectorVertOffset]) rotate([90,0,0]) cylinder(r=holeSizeBot,h=40,center=true);
        
        
    }

    
    
}

module servoConnectTwist(){
    
    armLength = 50;
    connectorLength = 50;
    armThickness = 4;
    armWidth = 17;
    innerHeight = 41;
    holeSize = 1.5;
    holeFromEdge = 16;
    holesEvery = 5;
    holeFromEdgeBot = 23;
    numHoles = 4;
    holeSizeBot = 2.5;
    connectorHeight = 16;
    connectorOffset = 3;
    connectorInnerWidth = 25;
    
    translate([-10+-armLength+30,+6-armWidth/2,-innerHeight/2+11])  difference(){
        
        color("red") 
        union(){
            
            translate([15,30,0]) rotate([0,0,-90]){
                translate([0,0,0]) cube([armLength, armWidth, armThickness]);
                translate([0,0,innerHeight]) cube([armLength, armWidth, armThickness]);
                translate([-armThickness,0,0]) cube([armThickness, armWidth, innerHeight+armThickness]);
            }
                
            translate([armLength/2-connectorInnerWidth/2-armThickness+connectorOffset,0,innerHeight]) cube([armThickness,armWidth,connectorLength]);
            translate([armLength/2+connectorInnerWidth/2-armThickness+connectorOffset,0,innerHeight]) cube([armThickness,armWidth,connectorLength]);
            
        };
        
        for (i = [0:numHoles-1]){translate([armLength-i*holesEvery-holeFromEdge,armWidth/2,innerHeight]) cylinder(r=holeSize,h=20,center=true);}
        translate([armLength-holeFromEdgeBot,armWidth/2,0]) cylinder(r=holeSizeBot,h=20,center=true);
        
        translate([armLength/2,armWidth/2,innerHeight+40]) rotate([0,90,0]) cylinder(r=holeSizeBot,h=40,center=true);
        translate([armLength/2,armWidth/2,innerHeight+10]) rotate([0,90,0]) cylinder(r=holeSizeBot,h=40,center=true);
 
    }
    
}

module foot(){
    
    thickness = 4;
    height = 16;
    holeSize = 2.5;
    connectorLength = 35;
    innerDistance = 29;
    supportLength = 12;
    supportWidth = 20;
    
    difference(){
    
        union(){
            
            translate([-connectorLength+25,innerDistance/2+thickness/2,0]) cube([connectorLength,thickness,height]);
            
            translate([-connectorLength+25,-innerDistance/2-thickness/2,0]) cube([connectorLength,thickness,height]);
            
            translate([-connectorLength+25,-innerDistance/2+thickness/2-supportLength,0]) cube([thickness,innerDistance+2*supportLength,height]);
            
            translate([-connectorLength+25,-supportWidth/2+thickness/2,height]) cube([thickness,supportWidth,supportLength]);
            translate([-connectorLength+25,-supportWidth/2+thickness/2,-supportLength]) cube([thickness,supportWidth,supportLength]);
                
        }
        
        translate([16,0,height/2]) rotate([90,0,0]) cylinder(r=holeSize,h=50,center=true);
        
    }
    
}

module leg(){
    
    hipToKnee = 100;
    
    rotate([0,-90,0]){

        servo();
        servoMountFixed();
        servoConnectStraight();

        translate([-hipToKnee,0,0]){
            servo();
            servoMountFixed();
            servoConnectStraight();
        }

        translate([-2*hipToKnee-20,4,-2.5]) foot();

        translate([67.5,0,-1]) rotate([90,0,-90]) {
            rotate([0,0,90]) {
                servo();
                servoMountFixed();
            }
            servoConnectTwist();
        }
        
    }
   
}

module bodyPlate(){
    
    thickness = 8;
    width = 120;
    length = 130;
    
    translate([0,0,0]) cube([width,length,thickness]);
    translate([0,0,8]) cube([4,40,15]);
    translate([-2,5,12.5]) rotate([0,90,0]) cylinder(r=2.5,h=10);
    translate([-2,35,12.5]) rotate([0,90,0]) cylinder(r=2.5,h=10);
    
}

module body(){
 
    translate([15,-17.5,50]) bodyPlate();
    translate([135,320,50]) rotate([0,0,180]) bodyPlate();
    translate([100,150,50]) rotate([90,0,0]) rotate([0,90,0]) {servo(); servoMountFixed();}
    
    
}

betweenLegs = 150;
catLength = 300;

//translate([0,0,0]) leg();
//translate([betweenLegs,0,0]) mirror([1,0,0])  leg();
//translate([betweenLegs,catLength,0]) mirror([1,0,0])  leg();
//translate([0,catLength,0])leg();
//translate([0,0,0]) body();

translate([0,0,0]) bodyPlate();
translate([200,0,0]) servo();
translate([300,0,0]) foot();
translate([400,0,0]) servoConnectTwist();
translate([600,0,0]) servoConnectStraight();
translate([700,0,0]) servoMountFixed();




