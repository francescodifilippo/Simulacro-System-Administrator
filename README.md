# Simulacro-System-Administrator

## English
Simulacro-System-Administrator is an advanced system for managing and automating remote connections, written in C. The project provides tools for executing remote commands, managing connections, and parsing XML data.

### Project History
This project was originally developed in 2005 and remained frozen for 20 years before being revisited. During this time, the source code was lost but later recovered from a backup and republished on GitHub (originally hosted on SourceForge). The original vision of the project was to be similar to **Ansible**, allowing automation and modular expansion, including a web interface. However, it was released in this version **seven years before Ansible**. In the future, it may be subject to further development and modifications.

### Project Structure
- **`estaconn/remoteconn/`**: Modules for managing remote connections.
- **`reaction/`**: Main system component with support for modules and extensions.
  - **`src/`**: Core source code.
  - **`modules/`**: Modules for expanding functionalities (`MOD_CONNECT`, `MOD_REG`, etc.), including an embedded scripting language based on **BScript**, a lightweight and portable BASIC interpreter developed by **Ariya Hidayat**. The system integrates **BScript** deeply, with execution contexts (`BSContext`), stack management (`BStack`), and predefined mathematical functions (`bhash_insert`).
  - **`parser/`**: Integrated XML parser.
  - **`docs/`**: Documentation.
- **Configuration and compilation files**: `Makefile.am`, `configure.in`, `INSTALL`.

### License
This project is distributed under the GNU General Public License v3 (GPLv3).  
You can read the full license in the `LICENSE` file or [here](https://www.gnu.org/licenses/gpl-3.0.txt).

---

## Italiano
Simulacro-System-Administrator è un sistema avanzato per la gestione e l'automazione delle connessioni remote, scritto in C. Il progetto fornisce strumenti per l'esecuzione di comandi remoti, la gestione delle connessioni e l'analisi dei dati XML.

### Storia del Progetto
Questo progetto è stato originariamente sviluppato nel 2005 ed è rimasto congelato per 20 anni prima di essere ripreso. Durante questo periodo, il codice sorgente è andato perso, ma è stato successivamente recuperato da un backup e ripubblicato su GitHub (originariamente ospitato su SourceForge). L'idea originale del progetto era di essere simile a **Ansible**, consentendo automazione e espansione modulare, incluso un'interfaccia web. Tuttavia, è stato rilasciato in questa versione **sette anni prima di Ansible**. In futuro, potrebbe essere soggetto a ulteriori sviluppi e modifiche.

### Struttura del Progetto
- **`estaconn/remoteconn/`**: Moduli per la gestione delle connessioni remote.
- **`reaction/`**: Componente principale del sistema con supporto per moduli ed estensioni.
  - **`src/`**: Codice sorgente principale.
  - **`modules/`**: Moduli per espandere le funzionalità (`MOD_CONNECT`, `MOD_REG`, etc.), incluso un linguaggio di scripting basato su **BScript**, un interprete BASIC portabile e leggero sviluppato da **Ariya Hidayat**. Il sistema integra **BScript** in profondità, con contesti di esecuzione (`BSContext`), gestione dello stack (`BStack`) e funzioni matematiche predefinite (`bhash_insert`).
  - **`parser/`**: Parser XML integrato.
  - **`docs/`**: Documentazione.
- **File di configurazione e compilazione**: `Makefile.am`, `configure.in`, `INSTALL`.

### Licenza
Questo progetto è distribuito sotto la GNU General Public License v3 (GPLv3).  
Puoi leggere il testo completo della licenza nel file `LICENSE` o [qui](https://www.gnu.org/licenses/gpl-3.0.txt).

---

## Latin
Simulacro-System-Administrator systema provectum est ad gubernandas et automandas connexiones remotas, in lingua C scriptum. Hoc projectum instrumenta praebet ad praecepta remota exequenda, connexionum administrationem, et XML data interpretanda.

### Historia Projecti
Hoc projectum anno 2005 conditum est et per 20 annos congelatum mansit antequam renovaretur. Per hoc tempus, codex amissus est, sed ex tergum recuperatus et iterum in GitHub (olim in SourceForge) editus est. Intentio originalis erat ut simile esset **Ansible**, automationem et expansionem modularis cum interfacie web permittens. Nihilominus, haec versio **septem annis ante Ansible** publicata est. In futurum, ulterius evolvi et mutari potest.

### Structura Projecti
- **`estaconn/remoteconn/`**: Moduli pro administratione connexionum remotarum.
- **`reaction/`**: Pars principalis systematis cum subsidiis modulorum et extensionum.
  - **`src/`**: Codex principalis.
  - **`modules/`**: Moduli ad facultates expandendas (`MOD_CONNECT`, `MOD_REG`, etc.), inclusum est lingua scriptoria ex **BScript**, interprete BASIC portabili et levi, a **Ariya Hidayat** creato. Systema **BScript** in se integrat, cum contextibus exsecutionis (`BSContext`), administratione aggeris (`BStack`), et functionibus mathematicis praedefinitis (`bhash_insert`).
  - **`parser/`**: XML interpretator integratus.
  - **`docs/`**: Documentatio.
- **Configurationis et compilationis fasciculi**: `Makefile.am`, `configure.in`, `INSTALL`.

### Licentia
Hoc projectum sub GNU General Public License v3 (GPLv3) distribuitur.  
Plenum textum licentiae in fasciculo `LICENSE` vel [hic](https://www.gnu.org/licenses/gpl-3.0.txt) legere potes.

