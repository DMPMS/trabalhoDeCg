//variaveis do tipo uniform são valores constantes para todos os fragmentos ou vértices do shader
uniform vec3 luzPosicao;

//valores recebidos do vertex shader através de interpolação linear (devem ter o mesmo nome)
varying vec3 posicao;
varying vec3 minhaNormal;
varying vec3 color;

//É possível criar funções em GLSL (OpenGL Shading Language) assim como nas linguagem C/C++
//Modelo de iluminação de Phong
vec3 sombreamento(){
    vec3 Ia = vec3(0.1,0.1,0.1);
    vec3 Id = vec3(1.0,1.0,1.0);

    vec3 V = normalize(-posicao); //o ponto está em coordenada de câmera, entao o vetor V é calculado assim
    vec3 N = normalize(minhaNormal);
    vec3 L = normalize(luzPosicao - posicao);

    vec3 Ra = vec3(0.1,0.1,0.1);
    vec3 Rd = max(dot(L,N),0.0) * color; //usando glColor como componente de material difusa

    vec3 ambiente = Ia * Ra;
    vec3 difusa   = Id * Rd;

    vec3 corFinal = ambiente+difusa; //somando todas as componentes (especular ausente)

    return corFinal;
}

void main(void){
    vec3 corFinal = sombreamento();
    //a variável interna gl_FragColor deve receber a cor que o fragmento irá aparecer na tela
    //todo fragment shader deve atribuir uma cor a essa variavel no final. Neste caso, a cor calculada pela função de sombreamento
    gl_FragColor = vec4(corFinal, 1.0);
}
