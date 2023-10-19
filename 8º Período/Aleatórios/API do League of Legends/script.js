var API_KEY= "API"
var br_url = "https://br1.api.riotgames.com";
var nome_invocador = ""

function buscar_invocador(){
    nome_invocador = document.getElementById("nome_do_invocador").value;
    console.log(nome_invocador);
    data();
}

async function data(){
    var nomeInvocadorUrl = "/lol/summoner/v4/summoners/by-name/"+nome_invocador;
    var pesquisaBR = br_url+nomeInvocadorUrl+"?api_key="+API_KEY;
    const dataInvocador_1 = await fetch (pesquisaBR);
    const invocador_tudo = await dataInvocador_1.json();
    console.log(invocador_tudo);

    // Nome de Invocador
    nome_invocador = invocador_tudo.name;
    document.getElementById("nome_invocador_data").innerHTML = nome_invocador;
    // Nivel
    var nivel_invocador = invocador_tudo.summonerLevel;
    console.log(nivel_invocador);
    document.getElementById("nivel_invocador").innerHTML = "O nível de "+nome_invocador+" é: "+nivel_invocador;

    // Foto de perfil
    var profile_pic_number = invocador_tudo.profileIconId;
    var profile_pic_url = "http://ddragon.leagueoflegends.com/cdn/13.19.1/img/profileicon/"+profile_pic_number+".png";
    document.getElementById("foto_invocador").src = profile_pic_url;
}