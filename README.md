# Esp32_uart_class

## Simple class for initialization of uart ports on esp32

#### Steps how to run it:

```bash
git clone https://github.com/bkresaj/Esp32_uart_class.git
```

#### Run docker container inside folder(firstly it will download docker image):

```bash
docker run --rm -v $PWD:/project -w /project -u $UID -e HOME=/tmp -it --device=<esp32_port_when_connected> espressif/idf
```

#### Inside docker container:
```bash
cd /example
```

#### For building source code
```bash
idf.py build
```

#### For flashing code to esp32
```bash
idf.py flash --port <esp32_port_name>
```

#### For monitoring logs from esp32
```bash
idf.py monitor -- port <esp32_port_name>
```

#### For deleting build folder
```bash
idf.py clean
```