#include <string>

#include "gtest/gtest.h"
#include "OrderDTO.hpp"
#include "Common.hpp"

TEST(OrderDtoTest, ToJsonSuccess) {

    OrderDTO order(0, "sell", 60, 1);

    nlohmann::json json = order.toJson();
    
    ASSERT_EQ(json["Direction"], order.direction);
    ASSERT_EQ(json["TraderId"], order.traderId);
    ASSERT_EQ(json["Price"], order.price);
    ASSERT_EQ(json["Amount"], order.amount);

}

TEST(OrderDtoTest, FromJsonSuccess) {

    
    OrderDTO clientOrder = OrderDTO(0, "sell", 60, 1);
    nlohmann::json request;
            request["UserId"] = clientOrder.traderId;
            request["Message"] = clientOrder.toJson();
            request["ReqType"] = Requests::NewOrder;
    std::string r = request.dump();

    auto j = nlohmann::json::parse(r);
    OrderDTO serverOrder = OrderDTO::fromJson(j["Message"]);

    ASSERT_EQ(clientOrder.traderId, serverOrder.traderId);
}


