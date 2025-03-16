# Simulacro-System-Administrator

## English
Simulacro-System-Administrator is an advanced system for managing and automating remote connections, written in C. The project provides tools for executing remote commands, managing connections, and parsing XML data.

###  Project Structure
- **`estaconn/remoteconn/`**: Modules for managing remote connections.
- **`reaction/`**: Main system component with support for modules and extensions.
  - **`src/`**: Core source code.
  - **`modules/`**: Modules for expanding functionalities (`MOD_CONNECT`, `MOD_REG`, etc.).
  - **`parser/`**: Integrated XML parser.
  - **`docs/`**: Documentation.
- **Configuration and compilation files**: `Makefile.am`, `configure.in`, `INSTALL`.

###  Installation
1. Clone the repository or extract the archive.
2. Run:
   ```sh
   ./configure
   make
   sudo make install
   ```
3. Verify installation with:
   ```sh
   reaction --help
   ```

###  Usage
Run a remote command:
```sh
remoteconn -h <host> -c "ls -la"
```
For details:
```sh
man reaction
```

###  License
This project is distributed under the **GNU General Public License v3 (GPLv3)**.  
You can read the full license in the `LICENSE` file or [here](https://www.gnu.org/licenses/gpl-3.0.txt).

---

## Italiano
Simulacro-System-Administrator è un sistema avanzato per la gestione e l'automazione delle connessioni remote, scritto in C. Il progetto fornisce strumenti per l'esecuzione di comandi remoti, la gestione delle connessioni e l'analisi dei dati XML.

###  Struttura del Progetto
- **`estaconn/remoteconn/`**: Moduli per la gestione delle connessioni remote.
- **`reaction/`**: Componente principale del sistema con supporto per moduli ed estensioni.
  - **`src/`**: Codice sorgente principale.
  - **`modules/`**: Moduli per espandere le funzionalità (`MOD_CONNECT`, `MOD_REG`, etc.).
  - **`parser/`**: Parser XML integrato.
  - **`docs/`**: Documentazione.
- **File di configurazione e compilazione**: `Makefile.am`, `configure.in`, `INSTALL`.

###  Installazione
1. Clonare il repository o estrarre l'archivio.
2. Eseguire:
   ```sh
   ./configure
   make
   sudo make install
   ```
3. Verificare l'installazione con:
   ```sh
   reaction --help
   ```

###  Utilizzo
Eseguire un comando remoto:
```sh
remoteconn -h <host> -c "ls -la"
```
Per dettagli:
```sh
man reaction
```

###  Licenza
Questo progetto è distribuito sotto la **GNU General Public License v3 (GPLv3)**.  
Puoi leggere il testo completo della licenza nel file `LICENSE` o [qui](https://www.gnu.org/licenses/gpl-3.0.txt).

---

## Latin
Simulacro-System-Administrator systema provectum est ad gubernandas et automandas connexiones remotas, in lingua C scriptum. Hoc projectum instrumenta praebet ad praecepta remota exequenda, connexionum administrationem, et XML data interpretanda.

###  Structura Projecti
- **`estaconn/remoteconn/`**: Moduli pro administratione connexionum remotarum.
- **`reaction/`**: Pars principalis systematis cum subsidiis modulorum et extensionum.
  - **`src/`**: Codex principalis.
  - **`modules/`**: Moduli ad facultates expandendas (`MOD_CONNECT`, `MOD_REG`, etc.).
  - **`parser/`**: XML interpretator integratus.
  - **`docs/`**: Documentatio.
- **Configurationis et compilationis fasciculi**: `Makefile.am`, `configure.in`, `INSTALL`.

###  Installatio
1. Repositorium clone vel archivum extrahe.
2. Exequere:
   ```sh
   ./configure
   make
   sudo make install
   ```
3. Institutionem verifica cum:
   ```sh
   reaction --help
   ```

###  Usus
Praeceptum remotum exequere:
```sh
remoteconn -h <host> -c "ls -la"
```
Ad singula:
```sh
man reaction
```

###  Licentia
Hoc projectum sub **GNU General Public License v3 (GPLv3)** distribuitur.  
Plenum textum licentiae in fasciculo `LICENSE` vel [hic](https://www.gnu.org/licenses/gpl-3.0.txt) legere potes.

