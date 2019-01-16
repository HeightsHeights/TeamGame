xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Cube {
    FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 1.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Cube mesh
      8;
       1.000000; 1.000000;-1.000000;,
       1.000000;-1.000000;-1.000000;,
      -1.000000;-1.000000;-1.000000;,
      -1.000000; 1.000000;-1.000000;,
       1.000000; 0.999999; 1.000000;,
       0.999999;-1.000001; 1.000000;,
      -1.000000;-1.000000; 1.000000;,
      -1.000000; 1.000000; 1.000000;;
      6;
      4;3,2,1,0;,
      4;5,6,7,4;,
      4;1,5,4,0;,
      4;2,6,5,1;,
      4;3,7,6,2;,
      4;7,3,0,4;;
      MeshNormals { // Cube normals
        6;
         0.000000; 0.000000;-1.000000;,
         0.000000;-0.000000; 1.000000;,
         1.000000;-0.000000; 0.000000;,
        -0.000000;-1.000000;-0.000000;,
        -1.000000; 0.000000;-0.000000;,
         0.000000; 1.000000; 0.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Cube normals
      MeshMaterialList { // Cube material list
        1;
        6;
        0,
        0,
        0,
        0,
        0,
        0;
        Material Material {
           0.640000; 0.640000; 0.640000; 1.000000;;
           96.078431;
           0.500000; 0.500000; 0.500000;;
           0.000000; 0.000000; 0.000000;;
        }
      } // End of Cube material list
    } // End of Cube mesh
  } // End of Cube
} // End of Root
AnimationSet Global {
  Animation {
    {Cube}
    AnimationKey { // Rotation
      0;
      60;
      0;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      1;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      2;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      3;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      4;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      5;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      6;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      7;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      8;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      9;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      10;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      11;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      12;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      13;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      14;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      15;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      16;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      17;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      18;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      19;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      20;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      21;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      22;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      23;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      24;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      25;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      26;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      27;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      28;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      29;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      30;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      31;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      32;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      33;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      34;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      35;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      36;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      37;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      38;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      39;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      40;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      41;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      42;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      43;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      44;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      45;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      46;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      47;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      48;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      49;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      50;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      51;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      52;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      53;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      54;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      55;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      56;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      57;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      58;4;-1.000000, 0.000000, 0.000000, 0.000000;;,
      59;4;-1.000000, 0.000000, 0.000000, 0.000000;;;
    }
    AnimationKey { // Scale
      1;
      60;
      0;3; 1.000000, 1.000000, 1.000000;;,
      1;3; 1.000000, 1.000000, 1.000000;;,
      2;3; 1.000000, 1.000000, 1.000000;;,
      3;3; 1.000000, 1.000000, 1.000000;;,
      4;3; 1.000000, 1.000000, 1.000000;;,
      5;3; 1.000000, 1.000000, 1.000000;;,
      6;3; 1.000000, 1.000000, 1.000000;;,
      7;3; 1.000000, 1.000000, 1.000000;;,
      8;3; 1.000000, 1.000000, 1.000000;;,
      9;3; 1.000000, 1.000000, 1.000000;;,
      10;3; 1.000000, 1.000000, 1.000000;;,
      11;3; 1.000000, 1.000000, 1.000000;;,
      12;3; 1.000000, 1.000000, 1.000000;;,
      13;3; 1.000000, 1.000000, 1.000000;;,
      14;3; 1.000000, 1.000000, 1.000000;;,
      15;3; 1.000000, 1.000000, 1.000000;;,
      16;3; 1.000000, 1.000000, 1.000000;;,
      17;3; 1.000000, 1.000000, 1.000000;;,
      18;3; 1.000000, 1.000000, 1.000000;;,
      19;3; 1.000000, 1.000000, 1.000000;;,
      20;3; 1.000000, 1.000000, 1.000000;;,
      21;3; 1.000000, 1.000000, 1.000000;;,
      22;3; 1.000000, 1.000000, 1.000000;;,
      23;3; 1.000000, 1.000000, 1.000000;;,
      24;3; 1.000000, 1.000000, 1.000000;;,
      25;3; 1.000000, 1.000000, 1.000000;;,
      26;3; 1.000000, 1.000000, 1.000000;;,
      27;3; 1.000000, 1.000000, 1.000000;;,
      28;3; 1.000000, 1.000000, 1.000000;;,
      29;3; 1.000000, 1.000000, 1.000000;;,
      30;3; 1.000000, 1.000000, 1.000000;;,
      31;3; 1.000000, 1.000000, 1.000000;;,
      32;3; 1.000000, 1.000000, 1.000000;;,
      33;3; 1.000000, 1.000000, 1.000000;;,
      34;3; 1.000000, 1.000000, 1.000000;;,
      35;3; 1.000000, 1.000000, 1.000000;;,
      36;3; 1.000000, 1.000000, 1.000000;;,
      37;3; 1.000000, 1.000000, 1.000000;;,
      38;3; 1.000000, 1.000000, 1.000000;;,
      39;3; 1.000000, 1.000000, 1.000000;;,
      40;3; 1.000000, 1.000000, 1.000000;;,
      41;3; 1.000000, 1.000000, 1.000000;;,
      42;3; 1.000000, 1.000000, 1.000000;;,
      43;3; 1.000000, 1.000000, 1.000000;;,
      44;3; 1.000000, 1.000000, 1.000000;;,
      45;3; 1.000000, 1.000000, 1.000000;;,
      46;3; 1.000000, 1.000000, 1.000000;;,
      47;3; 1.000000, 1.000000, 1.000000;;,
      48;3; 1.000000, 1.000000, 1.000000;;,
      49;3; 1.000000, 1.000000, 1.000000;;,
      50;3; 1.000000, 1.000000, 1.000000;;,
      51;3; 1.000000, 1.000000, 1.000000;;,
      52;3; 1.000000, 1.000000, 1.000000;;,
      53;3; 1.000000, 1.000000, 1.000000;;,
      54;3; 1.000000, 1.000000, 1.000000;;,
      55;3; 1.000000, 1.000000, 1.000000;;,
      56;3; 1.000000, 1.000000, 1.000000;;,
      57;3; 1.000000, 1.000000, 1.000000;;,
      58;3; 1.000000, 1.000000, 1.000000;;,
      59;3; 1.000000, 1.000000, 1.000000;;;
    }
    AnimationKey { // Position
      2;
      60;
      0;3; 0.000000, 0.000000, 0.000000;;,
      1;3; 0.000000, 0.000000, 0.000000;;,
      2;3; 0.000000, 0.000000, 0.000000;;,
      3;3; 0.000000, 0.000000, 0.000000;;,
      4;3; 0.000000, 0.000000, 0.000000;;,
      5;3; 0.000000, 0.000000, 0.000000;;,
      6;3; 0.000000, 0.000000, 0.000000;;,
      7;3; 0.000000, 0.000000, 0.000000;;,
      8;3; 0.000000, 0.000000, 0.000000;;,
      9;3; 0.000000, 0.000000, 0.000000;;,
      10;3; 0.000000, 0.000000, 0.000000;;,
      11;3; 0.000000, 0.000000, 0.000000;;,
      12;3; 0.000000, 0.000000, 0.000000;;,
      13;3; 0.000000, 0.000000, 0.000000;;,
      14;3; 0.000000, 0.000000, 0.000000;;,
      15;3; 0.000000, 0.000000, 0.000000;;,
      16;3; 0.000000, 0.000000, 0.000000;;,
      17;3; 0.000000, 0.000000, 0.000000;;,
      18;3; 0.000000, 0.000000, 0.000000;;,
      19;3; 0.000000, 0.000000, 0.000000;;,
      20;3; 0.000000, 0.000000, 0.000000;;,
      21;3; 0.000000, 0.000000, 0.000000;;,
      22;3; 0.000000, 0.000000, 0.000000;;,
      23;3; 0.000000, 0.000000, 0.000000;;,
      24;3; 0.000000, 0.000000, 0.000000;;,
      25;3; 0.000000, 0.000000, 0.000000;;,
      26;3; 0.000000, 0.000000, 0.000000;;,
      27;3; 0.000000, 0.000000, 0.000000;;,
      28;3; 0.000000, 0.000000, 0.000000;;,
      29;3; 0.000000, 0.000000, 0.000000;;,
      30;3; 0.000000, 0.000000, 0.000000;;,
      31;3; 0.000000, 0.000000, 0.000000;;,
      32;3; 0.000000, 0.000000, 0.000000;;,
      33;3; 0.000000, 0.000000, 0.000000;;,
      34;3; 0.000000, 0.000000, 0.000000;;,
      35;3; 0.000000, 0.000000, 0.000000;;,
      36;3; 0.000000, 0.000000, 0.000000;;,
      37;3; 0.000000, 0.000000, 0.000000;;,
      38;3; 0.000000, 0.000000, 0.000000;;,
      39;3; 0.000000, 0.000000, 0.000000;;,
      40;3; 0.000000, 0.000000, 0.000000;;,
      41;3; 0.000000, 0.000000, 0.000000;;,
      42;3; 0.000000, 0.000000, 0.000000;;,
      43;3; 0.000000, 0.000000, 0.000000;;,
      44;3; 0.000000, 0.000000, 0.000000;;,
      45;3; 0.000000, 0.000000, 0.000000;;,
      46;3; 0.000000, 0.000000, 0.000000;;,
      47;3; 0.000000, 0.000000, 0.000000;;,
      48;3; 0.000000, 0.000000, 0.000000;;,
      49;3; 0.000000, 0.000000, 0.000000;;,
      50;3; 0.000000, 0.000000, 0.000000;;,
      51;3; 0.000000, 0.000000, 0.000000;;,
      52;3; 0.000000, 0.000000, 0.000000;;,
      53;3; 0.000000, 0.000000, 0.000000;;,
      54;3; 0.000000, 0.000000, 0.000000;;,
      55;3; 0.000000, 0.000000, 0.000000;;,
      56;3; 0.000000, 0.000000, 0.000000;;,
      57;3; 0.000000, 0.000000, 0.000000;;,
      58;3; 0.000000, 0.000000, 0.000000;;,
      59;3; 0.000000, 0.000000, 0.000000;;;
    }
  }
} // End of AnimationSet Global
