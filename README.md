## 🔥 Projeto: Animações e Controle de LEDs

Este projeto utiliza o **Raspberry Pi Pico W**, **teclado matricial**, e uma **matriz de LEDs 5x5 WS2812B** para criar diversas animações controladas dinamicamente por teclado.

### 📋 Funcionalidades

1. **Matriz de LEDs Animada:**
   - Exibição de diferentes animações, como rostos, formas geométricas e textos.
   - Controle das cores e intensidade dos LEDs.

2. **Controle via Teclado Matricial:**
   - Ações específicas atribuídas às teclas.
   - Mudança entre animações em tempo real.

3. **Diversas Animações:**
   - **Animação Maic:** Efeito progressivo em frames.
   - **Humberto Zig-Zag:** LEDs piscando em um padrão em zigue-zague.
   - **VINI:** Nome sendo desenhado na matriz.
   - **Gabriel Rosto Microbit:** Rosto animado piscando e sorrindo.
   - **Decio Cascata:** LEDs acendendo em cascata.
   - **Kaique LOVE:** Exibição das letras "L", "O", "V", "E" de forma sequencial.
   - Cores e padrões específicos para teclas especiais (`A`, `B`, `C`, `D`, `#`).

---

### 🛠️ Pré-requisitos

- **Hardware Necessário:**
  - Raspberry Pi Pico.
  - Matriz de LEDs WS2812B (5x5).
  - Teclado matricial 4x4.
  - Resistores e jumpers para conexões.

- **Software Necessário:**
  - Raspberry Pi Pico SDK configurado.
  - CMake para compilação.
  - VS Code com a extensão Raspberry Pi Pico
---

## 🛠️ Configurando o Projeto no VS Code

1. **Abra o VS Code** e **importe o projeto**:
   - Vá até a **Extensão Raspberry Pi Pico**.
   - Selecione **Import Project**.
   - Escolha a pasta do repositório clonado.
   - Clique em **Import**.

2. **Compilar o código**:
   - Utilize a opção de **Build** da extensão.

3. **Rodar a simulação no Wokwi**:
   - Abra o arquivo `diagram.json`.
   - Clique em **Play** para iniciar a simulação.

### 🎮 Controles de Teclas

| Tecla | Função                                      |
|-------|---------------------------------------------|
| `0`   | Animação Maic                               |
| `1`   | Animação Humberto Zig-Zag                   |
| `2`   | Animação do nome "VINI"                     |
| `3`   | Rosto piscando (Gabriel Rosto Microbit)     |
| `4`   | Animação "ANAC"                             |
| `5`   | Animação Decio Cascata                      |
| `6`   | Animação Kaique (LOVE)                      |
| `A`   | Exibe padrão de LED para tecla `A`          |
| `B`   | Exibe padrão de LED para tecla `B`          |
| `C`   | Exibe padrão de LED para tecla `C`          |
| `D`   | Exibe padrão de LED para tecla `D`          |
| `#`   | Ativa todos os LEDs em branco               |

---

### 📜 Estrutura do Código

1. **Teclado Matricial:**
   - Configurado para 4 colunas e 4 linhas.
   - Cada tecla mapeada para uma função ou animação específica.

2. **Matriz de LEDs:**
   - 25 LEDs controlados individualmente.
   - Biblioteca PIO utilizada para eficiência.

3. **Animações:**
   - Cada animação é armazenada em uma matriz de frames.
   - Funções dedicadas para exibição dinâmica.

4. **Arquivos Importantes:**
   - `framesAnimacao.c`: Contém os frames das animações.
   - `pio_matrix.pio.h`: Controla os LEDs da matriz.
   - `animacoesKaique.h`: Animação específica "LOVE".
   - `diagram.json`: Estrutura para simular o hardware do projeto

---

### 📸 Exemplos de Animações

- **Rosto Animado:**
  ```
  😊 Sorriso piscante!
  ```
- **Cascata de LEDs:**
  ```
  🌟 Efeito de cascata dinâmico.
  ```
- **LOVE:**
  ```
  ❤️ Letras desenhadas sequencialmente.
  ```

## Desenvolvedores

- Ana Carolina Gomes
- Décio Francis da Silva
- Gabriel Silva Sampaio
- Humberto Costa
- Kaique Almeida Barbosa
- Maic de Oliveira Santos
- Vinícius Ramos de Araújo

## Vídeo de Demonstração

[Assista ao vídeo de demonstração aqui](https://www.dropbox.com/scl/fi/ovgytv7j4utnk3mtn7y95/2025-01-28-21-02-34.mkv?rlkey=yia9k8oo79p3x682wps6fcmj2&st=g9d3co0e&dl=0)
