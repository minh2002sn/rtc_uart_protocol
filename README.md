# **Table of contents**
- [**Table of contents**](#table-of-contents)
- [**1. About this project**](#1-about-this-project)
- [**2. System overview**](#2-system-overview)
  - [**2.1. State machine diagram**](#21-State-machine-diagram)
  - [**2.2. Sequence diagram**](#22-sequence-diagram)
  - [**2.3. Data type**](#23-data-type)
- [**3. System design**](#3-system-design)
  - [**3.1. Firmware architecture**](#31-firmware-architecture)
    - [**3.1.1. System services layer**](#311-system-services-layer)
    - [**3.1.2. BSP layer**](#312-bsp-layer)
    - [**3.1.3. Middlewares layer**](#313-middlewares-layer)
    - [**3.1.4. Device drivers layer**](#314-device-drivers-layer)

# **1. About this project**
This project aims to convert epoch values received via UART to date and time values and then store them in the RTC DS1307. The system will also allow the input of commands via UART to get the current time and set alarms based on the data from the DS1307.

# **2. System overview**
## **2.1. State machine diagram**
Below is a State machine demonstrating what system uart process data.

![fsm_uart_process_data](./docs/fsm_uart_process_data.png)

Below is a State machine demonstrating what system mangager process data.

![fsm_mng_process_data](./docs/)

## **2.2. Sequence diagram**
Below is a sequence diagram demonstrating what system do.

![sequence_diagram](./docs/sequence_diagram_user_btn.png)

## **2.3. Data type**
In this project, the data will be transmitted with the following types (HEX):

![data_type](./docs/data_type.png)

- **UART_TYPE_SET_TIME**: (0x00)
  - **Len** (1 byte): 0x04
  - **Data** (4 byte): epoch time
- **UART_TYPE_GET_TIME**: (0X01)
  - **Len** (1 byte): 0x00
  - **Data** (0 byte)
- **UART_TYPE_SET_ALARM**: (0x02)
  - **Len** (1 byte): 0x03
  - **Data** (3 byte): hour | min | sec

# **3. System design**
## **3.1. Firmware architecture**
Firmware of project use this firmware architecture model:

![firmware_architecture](./docs/architecture.png)

### **3.1.1. System services layer**

![sys_svc_layer](./docs/pic/architecture_sys.png)

- **sys_data_mng**:
- **sys_mng**:
- **sys_uart**:

### **3.1.2. BSP layer**

![bsp_layer](./docs/pic/architecture_bsp.png)

- **bsp_layer**:

### **3.1.3. Middlewares layer**

![mid_layer_cbuffer](./docs/architecture_midwares.png)

- **cbuffer**: Circular buffer library.

- **epoch**: epoch library.

### **3.1.4. Device drivers layer**

![drv_ds1308](./docs/architecture_drv_ds1307.png)

- **drv_ds1307**: Initialize ds1307 and some basic functions.


