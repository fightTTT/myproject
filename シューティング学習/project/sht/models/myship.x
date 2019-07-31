xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 52;
 0.00000;-0.12683;-1.86097;,
 0.00000;-0.50000;0.80000;,
 -1.22613;-0.12683;-0.22613;,
 1.22613;-0.12683;-0.22613;,
 0.58990;0.35436;-1.57108;,
 1.13484;1.17178;-0.88989;,
 2.50000;2.10000;-3.40000;,
 1.95226;0.89930;-0.88989;,
 1.13484;0.49059;-0.20871;,
 1.40732;0.08188;-0.88989;,
 -0.58990;0.35436;-1.57108;,
 -2.50000;2.10000;-3.40000;,
 -1.13484;1.17178;-0.88989;,
 -1.95226;0.89930;-0.88989;,
 -1.13484;0.49059;-0.20871;,
 -1.40732;0.08188;-0.88989;,
 1.08989;-0.49930;-1.07108;,
 3.81463;-1.79791;-2.29721;,
 1.63484;-1.31672;-0.38990;,
 2.45226;-1.04425;-0.38990;,
 1.63484;-0.63554;0.29129;,
 1.90732;-0.22683;-0.38990;,
 -1.08989;-0.49930;-1.07108;,
 -1.63484;-1.31672;-0.38990;,
 -3.81463;-1.79791;-2.29721;,
 -2.45226;-1.04425;-0.38990;,
 -1.63484;-0.63554;0.29129;,
 -1.90732;-0.22683;-0.38990;,
 0.00000;0.82683;-0.08990;,
 0.54495;0.44537;-0.49861;,
 0.00000;0.55436;-1.04355;,
 -0.54495;0.44537;-0.49861;,
 0.00000;0.30000;1.50000;,
 0.68118;0.30913;-0.49861;,
 0.00000;0.41812;-1.17979;,
 0.00000;0.20000;1.80000;,
 -0.68118;0.30913;-0.49861;,
 0.00000;-0.10000;3.50000;,
 0.54495;-0.12683;1.81742;,
 -0.54495;-0.12683;1.81742;,
 -0.71742;0.41812;-1.35226;,
 -0.03624;0.00941;-1.89721;,
 -1.00000;0.80000;-2.60000;,
 0.71742;0.41812;-1.35226;,
 1.00000;0.80000;-2.60000;,
 0.03624;0.00941;-1.89721;,
 -1.31742;-0.53554;-1.45226;,
 -1.50000;-0.70000;-2.40000;,
 -0.63624;-0.12683;-1.99721;,
 1.31742;-0.53554;-1.45226;,
 0.63624;-0.12683;-1.99721;,
 1.50000;-0.70000;-2.40000;;
 
 60;
 3;0,1,2;,
 3;3,1,0;,
 3;4,5,6;,
 3;5,7,6;,
 3;5,8,7;,
 3;5,4,8;,
 3;7,9,6;,
 3;8,9,7;,
 3;4,9,8;,
 3;6,9,4;,
 3;10,11,12;,
 3;12,11,13;,
 3;12,13,14;,
 3;12,14,10;,
 3;13,11,15;,
 3;14,13,15;,
 3;10,14,15;,
 3;11,10,15;,
 3;16,17,18;,
 3;18,17,19;,
 3;18,19,20;,
 3;18,20,16;,
 3;19,17,21;,
 3;20,19,21;,
 3;16,20,21;,
 3;17,16,21;,
 3;22,23,24;,
 3;23,25,24;,
 3;23,26,25;,
 3;23,22,26;,
 3;25,27,24;,
 3;26,27,25;,
 3;22,27,26;,
 3;24,27,22;,
 3;28,29,30;,
 3;28,30,31;,
 3;28,32,29;,
 3;28,31,32;,
 4;33,3,0,34;,
 4;33,34,30,29;,
 4;35,33,29,32;,
 4;36,35,32,31;,
 4;34,0,2,36;,
 4;34,36,31,30;,
 3;35,37,38;,
 4;35,38,3,33;,
 4;39,35,36,2;,
 3;35,39,37;,
 3;38,37,1;,
 3;1,3,38;,
 3;1,37,39;,
 3;1,39,2;,
 3;40,41,42;,
 3;43,44,45;,
 3;42,41,40;,
 3;45,44,43;,
 3;46,47,48;,
 3;49,50,51;,
 3;48,47,46;,
 3;51,50,49;;
 
 MeshMaterialList {
  4;
  60;
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  2,
  2,
  1,
  2,
  2,
  2,
  1,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.949000;0.447000;0.059000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.237250;0.111750;0.014750;;
  }
  Material {
   0.741000;0.741000;0.741000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.185250;0.185250;0.185250;;
  }
  Material {
   0.706000;0.612000;0.325000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.176500;0.153000;0.081250;;
  }
  Material {
   0.439000;0.416000;0.431000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.109750;0.104000;0.107750;;
  }
 }
 MeshNormals {
  80;
  0.262263;0.959430;-0.103505;,
  0.504984;0.849995;0.149999;,
  0.288046;-0.957608;-0.004063;,
  -0.000000;-0.998962;0.045548;,
  -0.288046;-0.957608;-0.004063;,
  0.000000;-0.990309;-0.138879;,
  -0.858971;0.505678;0.080363;,
  -0.748580;0.640842;-0.170146;,
  0.257301;0.771893;0.581359;,
  0.229418;0.688245;0.688248;,
  0.805800;-0.537201;0.249201;,
  0.858971;0.505678;0.080363;,
  0.748580;0.640842;-0.170146;,
  -0.257301;0.771893;0.581359;,
  -0.229418;0.688245;0.688248;,
  -0.805800;-0.537201;0.249201;,
  -0.805573;-0.589184;-0.062559;,
  -0.539298;-0.721471;-0.434324;,
  0.251741;-0.755221;0.605200;,
  0.229417;-0.688248;0.688247;,
  0.740661;0.493775;0.455639;,
  0.805573;-0.589184;-0.062559;,
  0.539298;-0.721471;-0.434324;,
  -0.251741;-0.755221;0.605200;,
  -0.229417;-0.688248;0.688247;,
  -0.740661;0.493775;0.455639;,
  0.642964;0.761523;-0.081734;,
  0.675101;0.699454;0.234527;,
  0.000000;0.881468;-0.472244;,
  -0.642964;0.761523;-0.081734;,
  0.670410;0.723500;-0.164613;,
  0.634222;0.576329;-0.515371;,
  0.574992;0.795332;0.191914;,
  -0.670410;0.723500;-0.164613;,
  0.516891;0.839298;0.168532;,
  -0.516891;0.839298;0.168532;,
  0.577808;0.807832;0.116388;,
  -0.577808;0.807832;0.116388;,
  0.538670;-0.841457;0.042245;,
  -0.538670;-0.841457;0.042245;,
  0.280244;0.840720;0.463307;,
  -0.889297;0.323380;0.323382;,
  0.564767;-0.745639;-0.353641;,
  0.692636;-0.461758;0.554108;,
  -0.508094;-0.812946;0.284532;,
  0.198683;-0.804237;-0.560115;,
  -0.280244;0.840720;0.463307;,
  0.889297;0.323380;0.323382;,
  -0.564767;-0.745639;-0.353641;,
  -0.692636;-0.461758;0.554108;,
  0.508094;-0.812946;0.284532;,
  -0.198683;-0.804237;-0.560115;,
  0.271075;-0.813223;0.514963;,
  -0.889297;-0.323382;0.323381;,
  0.779038;0.519360;0.351234;,
  0.692635;0.461758;0.554108;,
  -0.508094;0.812947;0.284532;,
  0.160755;0.834667;-0.526772;,
  -0.271075;-0.813223;0.514963;,
  0.889297;-0.323382;0.323381;,
  -0.779038;0.519360;0.351234;,
  -0.692636;0.461758;0.554108;,
  0.508094;0.812947;0.284532;,
  -0.160755;0.834667;-0.526772;,
  -0.669121;0.705434;0.233754;,
  -0.675101;0.699454;0.234527;,
  0.629635;0.757730;-0.171478;,
  0.640327;0.578505;-0.505285;,
  -0.574992;0.795332;0.191914;,
  -0.634222;0.576329;-0.515371;,
  -0.640327;0.578505;-0.505285;,
  -0.629635;0.757730;-0.171478;,
  -0.504984;0.849995;0.149999;,
  0.380039;-0.915471;0.132222;,
  0.000000;-0.989204;0.146549;,
  -0.380039;-0.915471;0.132222;,
  -0.577808;-0.807832;-0.116388;,
  0.577808;-0.807832;-0.116388;,
  -0.538670;0.841457;-0.042245;,
  0.538670;0.841457;-0.042245;;
  60;
  3;5,3,4;,
  3;2,3,5;,
  3;6,6,7;,
  3;8,8,40;,
  3;8,9,8;,
  3;6,6,41;,
  3;10,10,42;,
  3;43,10,10;,
  3;44,44,44;,
  3;42,45,45;,
  3;11,12,11;,
  3;13,46,13;,
  3;13,13,14;,
  3;11,47,11;,
  3;15,48,15;,
  3;49,15,15;,
  3;50,50,50;,
  3;48,51,51;,
  3;16,17,16;,
  3;18,52,18;,
  3;18,18,19;,
  3;16,53,16;,
  3;20,54,20;,
  3;55,20,20;,
  3;56,56,56;,
  3;57,57,57;,
  3;21,21,22;,
  3;23,23,58;,
  3;23,24,23;,
  3;21,21,59;,
  3;25,25,60;,
  3;61,25,25;,
  3;62,62,62;,
  3;63,63,63;,
  3;0,26,28;,
  3;0,28,29;,
  3;0,27,26;,
  3;64,29,65;,
  4;30,66,67,31;,
  4;30,31,28,26;,
  4;32,30,26,27;,
  4;33,68,65,29;,
  4;69,70,71,33;,
  4;69,33,29,28;,
  3;32,1,34;,
  4;32,34,66,30;,
  4;35,68,33,71;,
  3;68,35,72;,
  3;73,74,3;,
  3;3,2,73;,
  3;3,74,75;,
  3;3,75,4;,
  3;36,36,36;,
  3;37,37,37;,
  3;76,76,76;,
  3;77,77,77;,
  3;38,38,38;,
  3;39,39,39;,
  3;78,78,78;,
  3;79,79,79;;
 }
}
