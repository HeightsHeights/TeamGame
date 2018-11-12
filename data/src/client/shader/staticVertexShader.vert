//頂点シェーダ
void main(void)
{
	//投影変換 (モデルビュー * プロジェクション) * 頂点座標
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	
	//ambient計算
	float4 ambient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;//ambientの計算

	//各種基本的なベクトルを計算
	vec3 N = normalize(gl_NormalMatrix * gl_Normal);//視点座標の法線＋正規化
	vec4 V =normalize(-gl_ModelViewMatrix * gl_Vertex);//視点座標系の頂点位置
	vec3 L = normalize(gl_LightSource[0].position.xyz - V.xyz);//頂点→光源へのベクトル

	//diffuse計算
	float NdotL = dot(N,L);
	vec4 diffuse = vec4( max(0.0,NdotL) ) * gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse;


	//specular計算(Bilnのモデルを使用)
	vec3 H = normalize(gl_LightSource[0].halfVector.xyz);
	float NdotH = dot(N,H);
	vec4 specular = pow(max(0.0,NdotH),gl_FrontMaterial.shininess);
	if(NdotL <=0)//条件によってはspecular無し
	{
		specular = 0;
	}
	specular = specular* gl_LightSource[0].specular * gl_FrontMaterial.specular;
	
	
	//出力色
	gl_FrontColor = ambient + diffuse + specular;

}