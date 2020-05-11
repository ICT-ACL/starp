#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "services.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using test::StrRequest;
using test::StrReply;
using test::Test;

class TestClient {
  public:
    TestClient(std::shared_ptr<Channel> channel)
        : stub_(Test::NewStub(channel)) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string Echo(const std::string& str) {
        // Data we are sending to the server.
        StrRequest request;
        request.set_str(str);

        // Container for the data we expect from the server.
        StrReply reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        Status status = stub_->Echo(&context, request, &reply);

        // Act upon its status.
        if (status.ok()) {
            return reply.str();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return "RPC failed";
        }
    }

  private:
    std::unique_ptr<Test::Stub> stub_;
};

int main(int argc, char** argv) {
    std::string str = "";
    if (argc > 1)
        str = argv[1];
    TestClient test(grpc::CreateChannel(
                        "localhost:50051", grpc::InsecureChannelCredentials()));
    std::string reply = test.Echo(str);
    std::cout << "Test received: " << reply << std::endl;

    return 0;
}
