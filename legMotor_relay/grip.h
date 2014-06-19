/*
 * grip.h
 *
 * GRIP (Gifu university Robocon circle Interface Protocol)
 *
 * マイコン間シリアル通信のプロトコルを定義します。
 * Created: 2011/12/30 5:28:30
 *  Author: Gifu university Robocon circle
 */ 



#ifndef GRIP_H_
#define GRIP_H_

/**
 * 割り込みを許可をする or しない
 */
typedef enum InterruptSwitch {
	/** 割り込みを許可しない */
	INTERRUPT_OFF = 0,
	/** 割り込みを許可する */
	INTERRUPT_ON = 1
} InterruptSwitch;

/**
 * 進行方向
 */
typedef enum MovementDirection {
	FORWARD = 0,
	BACKWARD = 1,
	LEFT_ROTATION = 2,
	RIGHT_ROTATION = 3,
	STOP = 4
} MovementDirection;

/**
 * 左右
 */
typedef enum TurnDirection {
    RIGHT = 0,
    LEFT = 1    
} TurnDirection;


/**
 * 上下
 */
typedef enum VerticalDirection {
    UPPER = 0,
    LOWER = 1
} VerticalDirection;

/**
 * 正負
 */
typedef enum PlusMinus {
    PLUS = 0,
    MINUS = 1
} PlusMinus;

/**
 * オン・オフ
 */
typedef enum OnOff {
	OFF = 0,
	ON = 1
} OnOff;


/************************************************************************/
/* モータドライバに伝えるモータの回転方向とスピード
 * direction: 回転方向(FORWARD or BACKWARD)(UPPER or LOWER)など
 * speed: スピード(7bitで)                                                                      
/************************************************************************/
typedef union RightMotorSignal {
	uint8_t key: 8;
	struct {
	    MovementDirection direction: 1;
		uint8_t speed: 7;
	};
} RightMotorSignal;

typedef union LeftMotorSignal {
	uint8_t key: 8;
	struct {
	    MovementDirection direction: 1;
		uint8_t speed: 7;
	};
} LeftMotorSignal;

typedef union UpDownSignal {
	uint8_t key: 8;
	struct {
		VerticalDirection direction: 1;
		uint8_t speed: 7;
	};
} UpDownSignal;

typedef union MotorSignal {
	uint8_t key: 8;
	struct {
	    MovementDirection direction: 1;
		uint8_t speed: 7;
	};
} MotorSignal;

/**
 * 回転
 * direction: 右回転 or 左回転
 * speed: スピード(0-127)
 */
typedef union TurnSignal {
	TurnDirection direction: 1;
	uint8_t speed: 7;
};


#endif /* GRIP_H_ */