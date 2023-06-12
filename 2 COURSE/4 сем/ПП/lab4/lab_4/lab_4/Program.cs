using Lec04LibN;

    ILogger logger1 = Logger.create();
    logger1.log("000000");
    logger1.log("010101");
    logger1.start("A");
    logger1.log("020202");
    logger1.start("B");
    logger1.log("030303");
    logger1.stop();
    logger1.log("040404");


    ILogger logger2 = Logger.create();
    logger1.log("050505");
    logger2.start("C");
    logger1.log("060606");
    logger2.start("D");
    logger1.log("070707");
    logger1.log("080808");
    logger2.stop();
    logger1.log("090909");
    logger1.log("101010");
    logger1.log("111111");
    logger2.stop();

    ILogger logger3 = Logger.create();
    logger3.log("121212");
    logger3.start("E");
    logger3.start("F");
    logger3.stop();
    logger3.stop();