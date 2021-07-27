using Grpc.Core;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using BaseGRpc;
using System.Threading;

namespace BaseGRpcService
{
    public class BaseGRpcService : BaseGRpc.BaseGRpcServer.BaseGRpcServerBase, IBaseGRpcService
    {
        private readonly ILogger<BaseGRpcService> _logger;
        private bool _waitingForEvent;
        private AutoResetEvent ResponseEvent = new AutoResetEvent(false);
        public BaseGRpcService(ILogger<BaseGRpcService> logger)
        {
            _logger = logger;
        }

        public override Task<HelloReply> SayHello(HelloRequest request, ServerCallContext context)
        {
            _logger.Log(LogLevel.Information, $"Received Hello from {request.Name}");
            return Task.FromResult(new HelloReply
            {
                Message = "Hello " + request.Name
            });
        }

        public override Task<VoidMessage> Handshake(VoidMessage request, ServerCallContext context)
        {
            _logger.Log(LogLevel.Information, $"Received Handshake from peer = {context.Peer}");
            return Task.FromResult(new VoidMessage { });
        }

        public override async Task<BoolMessage> clientStream(IAsyncStreamReader<IntMessage> requestStream, ServerCallContext context)
        {
            _logger.Log(LogLevel.Information, $"Received clientStream, opening stream");
            try
            {
                while (!context.CancellationToken.IsCancellationRequested && await requestStream.MoveNext())
                {
                    _logger.Log(LogLevel.Information, $"Received new request from stream");

                    var Message = requestStream.Current;
                    DoSomething(Message);
                }
            }

            catch (Exception ex)
            {
                _logger.Log(LogLevel.Information, $"catched error from clientStream error: {ex.Message}");
                return new BoolMessage() { Message = false };
            }

            _logger.Log(LogLevel.Information, $"exiting clientStream");
            return new BoolMessage() { Message = true };
        }

        public override async Task serverStream(BoolMessage request, IServerStreamWriter<BoolMessage> responseStream, ServerCallContext context)
        {
            _logger.Log(LogLevel.Information, $"Received serverStream, opening stream");
            try
            {
                var numOfMessagesToStream = 10;
                for (int i = 0; i < numOfMessagesToStream && !context.CancellationToken.IsCancellationRequested; i++)
                {
                    _logger.Log(LogLevel.Information, $"Sending reaponse to BaseGRpcClient");
                    await responseStream.WriteAsync(new BoolMessage() { Message = true });
                }
            }

            catch (Exception ex)
            {
                _logger.Log(LogLevel.Information, $"catched error from clientStream error: {ex.Message}");
            }
            _logger.Log(LogLevel.Information, $"exiting serverStream");
        }

        /// <summary>
        /// Created a base mechanisem including processing request and wait for an event, signaling to return a response.
        /// Before sending a response we check if IsCancellationRequested to interrupt stream and exit stream opration.
        /// </summary>
        /// <param name="requestStream"></param>
        /// <param name="responseStream"></param>
        /// <param name="context"></param>
        /// <returns></returns>
        public override async Task BidiStream(IAsyncStreamReader<IntMessage> requestStream, IServerStreamWriter<BoolMessage> responseStream, ServerCallContext context)
        {
            _logger.Log(LogLevel.Information, $"Received BidiStream, opening streams");
            try
            {
                while (!context.CancellationToken.IsCancellationRequested && await requestStream.MoveNext())
                {
                    _logger.Log(LogLevel.Information, $"Received new request from stream");

                    var Message = requestStream.Current;
                    DoSomething(Message);

                    //wait & response
                    var reaponse = WaitForReturnResponseEvent();
                    if (context.CancellationToken.IsCancellationRequested)
                    {
                        _logger.Log(LogLevel.Information, $"slice stream requested cancellation");
                        break;
                    }

                    _logger.Log(LogLevel.Information, $"Sending reaponse to BaseGRpcClient");
                    await responseStream.WriteAsync(reaponse);
                }

                _logger.Log(LogLevel.Information, $"exiting bidirectional stream");
                context.Status = Status.DefaultCancelled;
            }

            catch (Exception ex)
            {
                _logger.Log(LogLevel.Information, $"catched error from BidiStream error: {ex.Message}");
            }
        }

        private BoolMessage WaitForReturnResponseEvent()
        {
            _waitingForEvent = true;
            _logger.Log(LogLevel.Information, $" Waiting for event");
            ResponseEvent.WaitOne();
            _waitingForEvent = false;

            _logger.Log(LogLevel.Information, $" Received event");
            return new BoolMessage() { Message = true };
        }

        public bool RaiseResponseEvent()
        {
            if (_waitingForEvent)
            {
                _logger.Log(LogLevel.Information, $"Thread was waiting on ResponseEvent, Raising ResponseEvent event");
                ResponseEvent.Set();
                return true;
            }
            else
                _logger.Log(LogLevel.Information, $"No thread was waiting on ResponseEvent");
            return false;
        }

        private void DoSomething(IntMessage message)
        {
            //implement logic for requests process
        }
    }
}
