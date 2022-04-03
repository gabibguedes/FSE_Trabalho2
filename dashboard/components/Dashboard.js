import React, { useEffect } from "react";
import io from "socket.io-client"

const Dashboard = () => {
  const { NEXT_PUBLIC_SOCKET_URL } = process.env;
  const socket = io.connect(NEXT_PUBLIC_SOCKET_URL, {
    reconnection: true
  });

  useEffect(() => {
    socket.on('connect', () => {
      console.log('[SOCKET] Socket is conected.');
      socket.emit('dasboard', "{bla: 'a'}");
    });
  }, []);

  return (
    <div>
      <h1>Dashboard</h1>
      <p>A socket io client</p>
    </div>
  );
}

export default Dashboard;