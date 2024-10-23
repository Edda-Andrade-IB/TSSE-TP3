#include <stdint.h>
// Define statements
#define PERIPH_BASE 0x40000000UL //!< Peripheral base address in the alias region
#define APB1PERIPH_BASE PERIPH_BASE
#define I2C1_BASE (APB1PERIPH_BASE + 0x5400UL)
#define I2C1 ((I2C_TypeDef *)I2C1_BASE)
#define I2C_ANALOGFILTER_ENABLE 0x00000000U
#define HAL_I2C_ERROR_NONE 0x00000000U
#define HAL_I2C_ERROR_BERR 0x00000001U
#define HAL_I2C_ERROR_ARLO 0x00000002U
#define HAL_I2C_ERROR_AF 0x00000004U
#define HAL_I2C_ERROR_OVR 0x00000008U
#define HAL_I2C_ERROR_DMA 0x00000010U
#define HAL_I2C_ERROR_TIMEOUT 0x00000020U
#define HAL_I2C_ERROR_SIZE 0x00000040U
#define HAL_I2C_ERROR_DMA_PARAM 0x00000080U
#define HAL_I2C_WRONG_START 0x00000200U
#define I2C_DUTYCYCLE_2 0x00000000U
#define I2C_DUTYCYCLE_16_9 I2C_CCR_DUTY
#define I2C_ADDRESSINGMODE_7BIT 0x00004000U
#define I2C_ADDRESSINGMODE_10BIT (I2C_OAR1_ADDMODE | 0x00004000U)
#define I2C_DUALADDRESS_DISABLE 0x00000000U
#define I2C_DUALADDRESS_ENABLE I2C_OAR2_ENDUAL
#define I2C_GENERALCALL_DISABLE 0x00000000U
#define I2C_GENERALCALL_ENABLE I2C_CR1_ENGC
#define I2C_NOSTRETCH_DISABLE 0x00000000U
#define I2C_NOSTRETCH_ENABLE I2C_CR1_NOSTRETCH
#define I2C_MEMADD_SIZE_8BIT 0x00000001U
#define I2C_MEMADD_SIZE_16BIT 0x00000010U
#define I2C_DIRECTION_RECEIVE 0x00000000U
#define I2C_DIRECTION_TRANSMIT 0x00000001U
#define I2C_FIRST_FRAME 0x00000001U
#define I2C_FIRST_AND_NEXT_FRAME 0x00000002U
#define I2C_NEXT_FRAME 0x00000004U
#define I2C_FIRST_AND_LAST_FRAME 0x00000008U
#define I2C_LAST_FRAME_NO_STOP 0x00000010U
#define I2C_LAST_FRAME 0x00000020U
#define I2C_OTHER_FRAME (0x00AA0000U)
#define I2C_OTHER_AND_LAST_FRAME (0xAA000000U)
#define I2C_IT_BUF I2C_CR2_ITBUFEN
#define I2C_IT_EVT I2C_CR2_ITEVTEN
#define I2C_IT_ERR I2C_CR2_ITERREN
#define I2C_FLAG_OVR 0x00010800U
#define I2C_FLAG_AF 0x00010400U
#define I2C_FLAG_ARLO 0x00010200U
#define I2C_FLAG_BERR 0x00010100U
#define I2C_FLAG_TXE 0x00010080U
#define I2C_FLAG_RXNE 0x00010040U
#define I2C_FLAG_STOPF 0x00010010U
#define I2C_FLAG_ADD10 0x00010008U
#define I2C_FLAG_BTF 0x00010004U
#define I2C_FLAG_ADDR 0x00010002U
#define I2C_FLAG_SB 0x00010001U
#define I2C_FLAG_DUALF 0x00100080U
#define I2C_FLAG_GENCALL 0x00100010U
#define I2C_FLAG_TRA 0x00100004U
#define I2C_FLAG_BUSY 0x00100002U
#define I2C_FLAG_MSL 0x00100001U
#define I2C_TIMEOUT_FLAG 35U
#define I2C_TIMEOUT_BUSY_FLAG 25U
#define I2C_TIMEOUT_STOP_FLAG 5U
#define I2C_NO_OPTION_FRAME 0xFFFF0000U
#define I2C_STATE_MSK ((uint32_t)((uint32_t)((uint32_t)HAL_I2C_STATE_BUSY_TX | (uint32_t)HAL_I2C_STATE_BUSY_RX) & (uint32_t)(~((uint32_t)HAL_I2C_STATE_READY))))
#define I2C_STATE_NONE ((uint32_t)(HAL_I2C_MODE_NONE))
#define I2C_STATE_MASTER_BUSY_TX ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_MASTER))
#define I2C_STATE_MASTER_BUSY_RX ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_MASTER))
#define I2C_STATE_SLAVE_BUSY_TX ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_TX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_SLAVE))
#define I2C_STATE_SLAVE_BUSY_RX ((uint32_t)(((uint32_t)HAL_I2C_STATE_BUSY_RX & I2C_STATE_MSK) | (uint32_t)HAL_I2C_MODE_SLAVE))
#define I2C_CR1_SWRST_Pos         (15U)   
#define I2C_CR1_SWRST_Msk         (0x1UL << I2C_CR1_SWRST_Pos)  
#define I2C_CR1_SWRST             I2C_CR1_SWRST_Msk  
// Typedef struct statements
typedef __SIZE_TYPE__ size_t;

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

typedef enum
{
    HAL_I2C_MODE_NONE = 0x00U,
    HAL_I2C_MODE_MASTER = 0x10U,
    HAL_I2C_MODE_SLAVE = 0x20U,
    HAL_I2C_MODE_MEM = 0x40U
} HAL_I2C_ModeTypeDef;

typedef struct I2C_HandleTypeDef
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




