# Trabalho 2 de FSE

## Servidor Central

O servidor central foi implementado em Node.js e é o serviço que recebe, via socket, todas as atualizações de todos os sistemas distribuidos e disponibiliza um dashboard para visualização de todas as informações.

Esse serviço necessita de 2 portas, uma para o socket, outra para o acesso ao dashboard. Essas portas são configuradas diretamente no `Dockerfile`, com a seguinte configuração:
- Porta do socket: `10005`
- Porta do dashboard: `3002`

Para rodar o serviço na placa da Raspiberry Pi entre na pasta `central_server/` utilize os comandos abaixo:

```sh
docker build . -t central_server

docker run --security-opt seccomp:unconfined -p 3002:3002 -p 10005:10005 central_server
```

Para rodar o serviço em um computador linux ou mac, basta utilizar o comando abaixo na raiz do repositório:
```sh
docker-compose up
```

Com o servidor central rodando o dashboard estará disponivel em `localhost:3002`.

<!-- Porta (Servidor Central) 10005
Porta (Servidor Distribuído 1) 10105
Porta (Servidor Distribuído 2) 10205 -->
## Servidor Distribuido

O servidor distribuido foi desenvolvido em C e gerencia o andar do prédio com todos os sensores. Utiliza de um arquivo de configuração `config.json` para instanciar os valores das variáveis de configuração.

Para rodar esse serviço rode os comandos abaixo dentro da pasta `distributed_server/`:

```sh
make
make run
```
