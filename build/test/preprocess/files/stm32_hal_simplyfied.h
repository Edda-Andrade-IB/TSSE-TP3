





typedef long unsigned int size_t;



typedef enum

{

    HAL_I2C_MODE_NONE = 0x00U,

    HAL_I2C_MODE_MASTER = 0x10U,

    HAL_I2C_MODE_SLAVE = 0x20U,

    HAL_I2C_MODE_MEM = 0x40U



} HAL_I2C_ModeTypeDef;



typedef struct

{

    uint32_t CR1;

    uint32_t CR2;

    uint32_t OAR1;

    uint32_t OAR2;

    uint32_t DR;

    uint32_t SR1;

    uint32_t SR2;

    uint32_t CCR;

    uint32_t TRISE;

    uint32_t FLTR;

} I2C_TypeDef;















typedef enum

{

    HAL_OK = 0x00U,

    HAL_ERROR = 0x01U,

    HAL_BUSY = 0x02U,

    HAL_TIMEOUT = 0x03U

} HAL_StatusTypeDef;

typedef enum

{

    HAL_UNLOCKED = 0x00U,

    HAL_LOCKED = 0x01U

} HAL_LockTypeDef;



typedef struct

{

    uint32_t Channel;





    uint32_t Direction;







    uint32_t PeriphInc;





    uint32_t MemInc;





    uint32_t PeriphDataAlignment;





    uint32_t MemDataAlignment;





    uint32_t Mode;









    uint32_t Priority;





    uint32_t FIFOMode;









    uint32_t FIFOThreshold;





    uint32_t MemBurst;











    uint32_t PeriphBurst;









} DMA_InitTypeDef;



typedef enum

{

    HAL_DMA_STATE_RESET = 0x00U,

    HAL_DMA_STATE_READY = 0x01U,

    HAL_DMA_STATE_BUSY = 0x02U,

    HAL_DMA_STATE_TIMEOUT = 0x03U,

    HAL_DMA_STATE_ERROR = 0x04U,

    HAL_DMA_STATE_ABORT = 0x05U,

} HAL_DMA_StateTypeDef;



typedef struct

{

    uint32_t CR;

    uint32_t NDTR;

    uint32_t PAR;

    uint32_t M0AR;

    uint32_t M1AR;

    uint32_t FCR;

} DMA_Stream_TypeDef;



typedef struct

{

    DMA_Stream_TypeDef *Instance;



    DMA_InitTypeDef Init;

    HAL_LockTypeDef Lock;



    HAL_DMA_StateTypeDef State;



    void *Parent;

    uint32_t ErrorCode;



    uint32_t StreamBaseAddress;



    uint32_t StreamIndex;



} DMA_HandleTypeDef;



typedef struct

{

    uint32_t ClockSpeed;





    uint32_t DutyCycle;





    uint32_t OwnAddress1;





    uint32_t AddressingMode;





    uint32_t DualAddressMode;





    uint32_t OwnAddress2;





    uint32_t GeneralCallMode;





    uint32_t NoStretchMode;





} I2C_InitTypeDef;



typedef enum

{

    HAL_I2C_STATE_RESET = 0x00U,

    HAL_I2C_STATE_READY = 0x20U,

    HAL_I2C_STATE_BUSY = 0x24U,

    HAL_I2C_STATE_BUSY_TX = 0x21U,

    HAL_I2C_STATE_BUSY_RX = 0x22U,

    HAL_I2C_STATE_LISTEN = 0x28U,

    HAL_I2C_STATE_BUSY_TX_LISTEN = 0x29U,



    HAL_I2C_STATE_BUSY_RX_LISTEN = 0x2AU,



    HAL_I2C_STATE_ABORT = 0x60U,

    HAL_I2C_STATE_TIMEOUT = 0xA0U,

    HAL_I2C_STATE_ERROR = 0xE0U



} HAL_I2C_StateTypeDef;







typedef struct

{

    I2C_TypeDef *Instance;



    I2C_InitTypeDef Init;



    uint8_t *pBuffPtr;



    uint16_t XferSize;



    uint16_t XferCount;



    uint32_t XferOptions;



    uint32_t PreviousState;





    DMA_HandleTypeDef *hdmatx;



    DMA_HandleTypeDef *hdmarx;



    HAL_LockTypeDef Lock;



    HAL_I2C_StateTypeDef State;



    HAL_I2C_ModeTypeDef Mode;



    uint32_t ErrorCode;



    uint32_t Devaddress;



    uint32_t Memaddress;



    uint32_t MemaddSize;



    uint32_t EventCount;



} I2C_HandleTypeDef;





HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c,

                                          uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c,

                                         uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Slave_Transmit(I2C_HandleTypeDef *hi2c,

                                         uint8_t *pData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Slave_Receive(I2C_HandleTypeDef *hi2c, uint8_t *pData,

                                        uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c,

                                    uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize,

                                    uint8_t *pData, uint16_t Size, uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,

                                   uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size,

                                   uint32_t Timeout);

HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c,

                                        uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);

void HAL_Delay(uint32_t Delay);

uint32_t HAL_GetTick(void);

void *memset(void *s, int c, size_t n);

int assert(int);

HAL_StatusTypeDef HAL_I2CEx_ConfigAnalogFilter(I2C_HandleTypeDef *hi2c, uint32_t AnalogFilter);

HAL_StatusTypeDef HAL_I2CEx_ConfigDigitalFilter(I2C_HandleTypeDef *hi2c, uint32_t DigitalFilter);
