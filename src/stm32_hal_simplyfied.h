#include <stdint.h>

#define __SIZE_TYPE__ long unsigned int
typedef __SIZE_TYPE__ size_t;

typedef struct
{
    uint32_t CR1;   /*!< I2C Control register 1,     Address offset: 0x00 */
    uint32_t CR2;   /*!< I2C Control register 2,     Address offset: 0x04 */
    uint32_t OAR1;  /*!< I2C Own address register 1, Address offset: 0x08 */
    uint32_t OAR2;  /*!< I2C Own address register 2, Address offset: 0x0C */
    uint32_t DR;    /*!< I2C Data register,          Address offset: 0x10 */
    uint32_t SR1;   /*!< I2C Status register 1,      Address offset: 0x14 */
    uint32_t SR2;   /*!< I2C Status register 2,      Address offset: 0x18 */
    uint32_t CCR;   /*!< I2C Clock control register, Address offset: 0x1C */
    uint32_t TRISE; /*!< I2C TRISE register,         Address offset: 0x20 */
    uint32_t FLTR;  /*!< I2C FLTR register,          Address offset: 0x24 */
} I2C_TypeDef;

#define PERIPH_BASE           0x40000000UL //!< Peripheral base address in the alias region 
#define APB1PERIPH_BASE       PERIPH_BASE
#define I2C1_BASE             (APB1PERIPH_BASE + 0x5400UL)


#define I2C1                ((I2C_TypeDef *) I2C1_BASE)
#define I2C_ANALOGFILTER_ENABLE        0x00000000U
typedef enum {
	HAL_OK = 0x00U, HAL_ERROR = 0x01U, HAL_BUSY = 0x02U, HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

#define HAL_I2C_ERROR_NONE 0x00000000U      /*!< No error              */
#define HAL_I2C_ERROR_BERR 0x00000001U      /*!< BERR error            */
#define HAL_I2C_ERROR_ARLO 0x00000002U      /*!< ARLO error            */
#define HAL_I2C_ERROR_AF 0x00000004U        /*!< AF error              */
#define HAL_I2C_ERROR_OVR 0x00000008U       /*!< OVR error             */
#define HAL_I2C_ERROR_DMA 0x00000010U       /*!< DMA transfer error    */
#define HAL_I2C_ERROR_TIMEOUT 0x00000020U   /*!< Timeout Error         */
#define HAL_I2C_ERROR_SIZE 0x00000040U      /*!< Size Management error */
#define HAL_I2C_ERROR_DMA_PARAM 0x00000080U /*!< DMA Parameter Error   */
#define HAL_I2C_WRONG_START 0x00000200U     /*!< Wrong start Error     */
#define I2C_DUTYCYCLE_2 0x00000000U
#define I2C_DUTYCYCLE_16_9 I2C_CCR_DUTY
/**
 * @}
 */

/** @defgroup I2C_addressing_mode I2C addressing mode
 * @{
 */
#define I2C_ADDRESSINGMODE_7BIT 0x00004000U
#define I2C_ADDRESSINGMODE_10BIT (I2C_OAR1_ADDMODE | 0x00004000U)
/**
 * @}
 */

/** @defgroup I2C_dual_addressing_mode  I2C dual addressing mode
 * @{
 */
#define I2C_DUALADDRESS_DISABLE 0x00000000U
#define I2C_DUALADDRESS_ENABLE I2C_OAR2_ENDUAL
/**
 * @}
 */

/** @defgroup I2C_general_call_addressing_mode I2C general call addressing mode
 * @{
 */
#define I2C_GENERALCALL_DISABLE 0x00000000U
#define I2C_GENERALCALL_ENABLE I2C_CR1_ENGC
/**
 * @}
 */

/** @defgroup I2C_nostretch_mode I2C nostretch mode
 * @{
 */
#define I2C_NOSTRETCH_DISABLE 0x00000000U
#define I2C_NOSTRETCH_ENABLE I2C_CR1_NOSTRETCH
/**
 * @}
 */

/** @defgroup I2C_Memory_Address_Size I2C Memory Address Size
 * @{
 */
#define I2C_MEMADD_SIZE_8BIT 0x00000001U
#define I2C_MEMADD_SIZE_16BIT 0x00000010U
/**
 * @}
 */

/** @defgroup I2C_XferDirection_definition I2C XferDirection definition
 * @{
 */
#define I2C_DIRECTION_RECEIVE 0x00000000U
#define I2C_DIRECTION_TRANSMIT 0x00000001U
/**
 * @}
 */

/** @defgroup I2C_XferOptions_definition I2C XferOptions definition
 * @{
 */
#define I2C_FIRST_FRAME 0x00000001U
#define I2C_FIRST_AND_NEXT_FRAME 0x00000002U
#define I2C_NEXT_FRAME 0x00000004U
#define I2C_FIRST_AND_LAST_FRAME 0x00000008U
#define I2C_LAST_FRAME_NO_STOP 0x00000010U
#define I2C_LAST_FRAME 0x00000020U

/* List of XferOptions in usage of :
 * 1- Restart condition in all use cases (direction change or not)
 */
#define I2C_OTHER_FRAME (0x00AA0000U)
#define I2C_OTHER_AND_LAST_FRAME (0xAA000000U)
/**
 * @}
 */

/** @defgroup I2C_Interrupt_configuration_definition I2C Interrupt configuration definition
 * @brief I2C Interrupt definition
 *        Elements values convention: 0xXXXXXXXX
 *           - XXXXXXXX  : Interrupt control mask
 * @{
 */
#define I2C_IT_BUF I2C_CR2_ITBUFEN
#define I2C_IT_EVT I2C_CR2_ITEVTEN
#define I2C_IT_ERR I2C_CR2_ITERREN
/**
 * @}
 */

/** @defgroup I2C_Flag_definition I2C Flag definition
 * @{
 */

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

typedef enum
{
    HAL_UNLOCKED = 0x00U,
    HAL_LOCKED = 0x01U
} HAL_LockTypeDef;

typedef struct
{
    uint32_t Channel; /*!< Specifies the channel used for the specified stream.
     This parameter can be a value of @ref DMA_Channel_selection                    */

    uint32_t Direction; /*!< Specifies if the data will be transferred from memory to peripheral,
     from memory to memory or from peripheral to memory.
     This parameter can be a value of @ref DMA_Data_transfer_direction              */

    uint32_t PeriphInc; /*!< Specifies whether the Peripheral address register should be incremented or not.
     This parameter can be a value of @ref DMA_Peripheral_incremented_mode          */

    uint32_t MemInc; /*!< Specifies whether the memory address register should be incremented or not.
     This parameter can be a value of @ref DMA_Memory_incremented_mode              */

    uint32_t PeriphDataAlignment; /*!< Specifies the Peripheral data width.
     This parameter can be a value of @ref DMA_Peripheral_data_size                 */

    uint32_t MemDataAlignment; /*!< Specifies the Memory data width.
     This parameter can be a value of @ref DMA_Memory_data_size                     */

    uint32_t Mode; /*!< Specifies the operation mode of the DMAy Streamx.
     This parameter can be a value of @ref DMA_mode
     @note The circular buffer mode cannot be used if the memory-to-memory
     data transfer is configured on the selected Stream                        */

    uint32_t Priority; /*!< Specifies the software priority for the DMAy Streamx.
     This parameter can be a value of @ref DMA_Priority_level                       */

    uint32_t FIFOMode; /*!< Specifies if the FIFO mode or Direct mode will be used for the specified stream.
     This parameter can be a value of @ref DMA_FIFO_direct_mode
     @note The Direct mode (FIFO mode disabled) cannot be used if the
     memory-to-memory data transfer is configured on the selected stream       */

    uint32_t FIFOThreshold; /*!< Specifies the FIFO threshold level.
     This parameter can be a value of @ref DMA_FIFO_threshold_level                  */

    uint32_t MemBurst; /*!< Specifies the Burst transfer configuration for the memory transfers.
     It specifies the amount of data to be transferred in a single non interruptible
     transaction.
     This parameter can be a value of @ref DMA_Memory_burst
     @note The burst mode is possible only if the address Increment mode is enabled. */

    uint32_t PeriphBurst; /*!< Specifies the Burst transfer configuration for the peripheral transfers.
     It specifies the amount of data to be transferred in a single non interruptible
     transaction.
     This parameter can be a value of @ref DMA_Peripheral_burst
     @note The burst mode is possible only if the address Increment mode is enabled. */
} DMA_InitTypeDef;

typedef enum
{
    HAL_DMA_STATE_RESET = 0x00U,   /*!< DMA not yet initialized or disabled */
    HAL_DMA_STATE_READY = 0x01U,   /*!< DMA initialized and ready for use   */
    HAL_DMA_STATE_BUSY = 0x02U,    /*!< DMA process is ongoing              */
    HAL_DMA_STATE_TIMEOUT = 0x03U, /*!< DMA timeout state                   */
    HAL_DMA_STATE_ERROR = 0x04U,   /*!< DMA error state                     */
    HAL_DMA_STATE_ABORT = 0x05U,   /*!< DMA Abort state                     */
} HAL_DMA_StateTypeDef;

typedef struct
{
    uint32_t CR;   /*!< DMA stream x configuration register      */
    uint32_t NDTR; /*!< DMA stream x number of data register     */
    uint32_t PAR;  /*!< DMA stream x peripheral address register */
    uint32_t M0AR; /*!< DMA stream x memory 0 address register   */
    uint32_t M1AR; /*!< DMA stream x memory 1 address register   */
    uint32_t FCR;  /*!< DMA stream x FIFO control register       */
} DMA_Stream_TypeDef;

typedef struct
{
    DMA_Stream_TypeDef *Instance; /*!< Register base address                  */

    DMA_InitTypeDef Init; /*!< DMA communication parameters           */
    HAL_LockTypeDef Lock; /*!< DMA locking object                     */

    HAL_DMA_StateTypeDef State; /*!< DMA transfer state                     */

    void *Parent; /*!< Parent object state                    */

    // void (*XferCpltCallback)(struct __DMA_HandleTypeDef *hdma); /*!< DMA transfer complete callback         */

    // void (*XferHalfCpltCallback)(struct __DMA_HandleTypeDef *hdma); /*!< DMA Half transfer complete callback    */

    // void (*XferM1CpltCallback)(struct __DMA_HandleTypeDef *hdma); /*!< DMA transfer complete Memory1 callback */

    // void (*XferM1HalfCpltCallback)(struct __DMA_HandleTypeDef *hdma); /*!< DMA transfer Half complete Memory1 callback */

    // void (*XferErrorCallback)(struct __DMA_HandleTypeDef *hdma); /*!< DMA transfer error callback            */

    // void (*XferAbortCallback)(struct __DMA_HandleTypeDef *hdma); /*!< DMA transfer Abort callback            */

    uint32_t ErrorCode; /*!< DMA Error code                          */

    uint32_t StreamBaseAddress; /*!< DMA Stream Base Address                */

    uint32_t StreamIndex; /*!< DMA Stream Index                       */

} DMA_HandleTypeDef;


typedef struct
{
    uint32_t ClockSpeed; /*!< Specifies the clock frequency.
     This parameter must be set to a value lower than 400kHz */

    uint32_t DutyCycle; /*!< Specifies the I2C fast mode duty cycle.
     This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

    uint32_t OwnAddress1; /*!< Specifies the first device own address.
     This parameter can be a 7-bit or 10-bit address. */

    uint32_t AddressingMode; /*!< Specifies if 7-bit or 10-bit addressing mode is selected.
     This parameter can be a value of @ref I2C_addressing_mode */

    uint32_t DualAddressMode; /*!< Specifies if dual addressing mode is selected.
     This parameter can be a value of @ref I2C_dual_addressing_mode */

    uint32_t OwnAddress2; /*!< Specifies the second device own address if dual addressing mode is selected
     This parameter can be a 7-bit address. */

    uint32_t GeneralCallMode; /*!< Specifies if general call mode is selected.
     This parameter can be a value of @ref I2C_general_call_addressing_mode */

    uint32_t NoStretchMode; /*!< Specifies if nostretch mode is selected.
     This parameter can be a value of @ref I2C_nostretch_mode */

} I2C_InitTypeDef;

typedef enum
{
    HAL_I2C_STATE_RESET = 0x00U,          /*!< Peripheral is not yet Initialized         */
    HAL_I2C_STATE_READY = 0x20U,          /*!< Peripheral Initialized and ready for use  */
    HAL_I2C_STATE_BUSY = 0x24U,           /*!< An internal process is ongoing            */
    HAL_I2C_STATE_BUSY_TX = 0x21U,        /*!< Data Transmission process is ongoing      */
    HAL_I2C_STATE_BUSY_RX = 0x22U,        /*!< Data Reception process is ongoing         */
    HAL_I2C_STATE_LISTEN = 0x28U,         /*!< Address Listen Mode is ongoing            */
    HAL_I2C_STATE_BUSY_TX_LISTEN = 0x29U, /*!< Address Listen Mode and Data Transmission
     process is ongoing                         */
    HAL_I2C_STATE_BUSY_RX_LISTEN = 0x2AU, /*!< Address Listen Mode and Data Reception
     process is ongoing                         */
    HAL_I2C_STATE_ABORT = 0x60U,          /*!< Abort user request ongoing                */
    HAL_I2C_STATE_TIMEOUT = 0xA0U,        /*!< Timeout state                             */
    HAL_I2C_STATE_ERROR = 0xE0U           /*!< Error                                     */

} HAL_I2C_StateTypeDef;

typedef enum
{
    HAL_I2C_MODE_NONE = 0x00U,   /*!< No I2C communication on going             */
    HAL_I2C_MODE_MASTER = 0x10U, /*!< I2C communication is in Master Mode       */
    HAL_I2C_MODE_SLAVE = 0x20U,  /*!< I2C communication is in Slave Mode        */
    HAL_I2C_MODE_MEM = 0x40U     /*!< I2C communication is in Memory Mode       */

} HAL_I2C_ModeTypeDef;


typedef struct
{
    I2C_TypeDef *Instance; /*!< I2C registers base address               */

    I2C_InitTypeDef Init; /*!< I2C communication parameters             */

    uint8_t *pBuffPtr; /*!< Pointer to I2C transfer buffer           */

    uint16_t XferSize; /*!< I2C transfer size                        */

    uint16_t XferCount; /*!< I2C transfer counter                     */

    uint32_t XferOptions; /*!< I2C transfer options                     */

    uint32_t PreviousState; /*!< I2C communication Previous state and mode
     context for internal usage               */

    DMA_HandleTypeDef *hdmatx; /*!< I2C Tx DMA handle parameters             */

    DMA_HandleTypeDef *hdmarx; /*!< I2C Rx DMA handle parameters             */

    HAL_LockTypeDef Lock; /*!< I2C locking object                       */

    HAL_I2C_StateTypeDef State; /*!< I2C communication state                  */

    HAL_I2C_ModeTypeDef Mode; /*!< I2C communication mode                   */

    uint32_t ErrorCode; /*!< I2C Error code                           */

    uint32_t Devaddress; /*!< I2C Target device address                */

    uint32_t Memaddress; /*!< I2C Target memory address                */

    uint32_t MemaddSize; /*!< I2C Target memory address  size          */

    uint32_t EventCount; /*!< I2C Event counter                        */

} I2C_HandleTypeDef;

HAL_StatusTypeDef HAL_I2C_Init(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef HAL_I2C_DeInit(I2C_HandleTypeDef *hi2c);



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