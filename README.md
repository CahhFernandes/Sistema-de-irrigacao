# Sistema-de-irrigacao

  Para realizar esse projeto, foi usado uma válvula solenoide de entrada e saída de água, ela funciona com uma tensão de 12V DC, ela é conectada a uma mangueira com fluxo contínuo, e quem faz a regulagem é o Relé, que recebe as instruções do Arduino UNO acionado a partir do sensor de umidade de solo, e nele também está conectado o NodeMCU utilizado apenas para conexão WI-FI. 
	Os dados são enviados e armazenados na plataforma ThingSpeak, onde pode ser visto os dados por meio de gráficos. O modo de comunicação é o MQTT. 
