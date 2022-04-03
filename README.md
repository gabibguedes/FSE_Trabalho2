# Trabalho 2 de FSE

2 códigos:

1 para o central
1 para o distribuido


Servidor central:
- Pode ser em python, JS, C ou C++
- Mostra as atualizações de todos os dados
- Aciona lampadas e alarme
- Mantem log

Servidor distribuido
- Em C ou C++
- Valores de temperatura e umidade atualizados a cada segundo
- Acionar lampadas, ar, e aspersores de incendio via mensagem do servidor central
- Sensores de presença e abertura de portas e janelas
- Sensores de fumaça mandando ao servidor central qndo ativado
- Fazer a contagem de pessoas pelo sensor de presença
- Ler do arquivo de configuração para setar as variáveis

- comunicaçao json entre os serviços -> biblioteca cjson


TODO:
- sockets
  - central server
  - dashboard
  - distributed server

- distribuido
  - ler arquivo de conf
  - ler inputs dos sensores
  - enviar e receber dados do central

- central
  - implementar dashboard
  - receber dados para o dash
  - enviar comandos
