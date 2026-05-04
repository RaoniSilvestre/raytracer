# RTX ON at home

Raytracer em progresso como parte da disciplina de Computação Gráfica I na UFRN.

# Como compilar o projeto 

## Pré requisitos

- Compilador C++: `Clang`
- Sistema de build: `CMake`
- Command runner: `just`

## Rodando o projeto

O projeto utiliza `just`(tipo um make mais moderninho) para simplificar o workflow de setup e de rodar o projeto.

Considerando que você tem o just, o CMake e o Clang no `PATH`, faça o seguinte:

1. Setup

```sh
just setup
```

2. Build & run

```sh
just run
```

3. Opcional, selecionar outra cena

```sh
just run scenes/cena-que-voce-quer-rodar.xml
```


# Componentes da equipe

- Raoni Marti Silvestre Silva
- Arthur José Arruda Skeete

# O que foi implementado

Lista de todas as implementações concluídas:

## Projeto 1 (Fundação)

- [X] Classe Film que exporta tanto para `.ppm` quanto para `.png`
- [X] Classe Background usando interpolação bilinear
- [X] Classe API básica
- [X] Main loop que renderiza as cores do background
- [X] Estruturação de parsing de `.xml` para as próximas atividades

## Projeto 2 (Raios e Câmeras)

- [X] Classe Ray, estrutura básica do Raytracer
- [X] Classes relacionadas a câmera (ortográfica e em perspectiva), que geram raios
- [X] Implementação de parsing de raios e câmeras

## Projeto 3 (Objetos e superfícies)

- [X] Classe Primitive, que indica se houve alguma interseção de um objeto na cena com o raio gerado pela câmera(proj. 3).
- [X] Classe Surfel, que guarda informações geométricas de uma superfície (útil para o proj 4)
- [X] Classe Sphere, a implementação de um `Primitive` (mudou depois)
- [X] Incrementação do parser para suportar essas novas classes

> A partir daqui ficou legal, foi possível renderizar esferas na tela

## Projeto 4 (Integradores e materiais)

- [X] Refatoração da estrutura de classes para suportar as próximas atividades
- [X] Criação de integradores
- [X] Criação de flat material

### Extras concluídos

- [X] Depth integrator (In progress)
- [X] Normal Map Integrator

## Projeto 5 (Modelo reflexivo Blinn-Phong)

- [ ] Classe LightSource
- [ ] Novos materiais
- [ ] Implementar o integrador Blinn-Phong

## Projeto 6 (...)

- [ ] ...
