import React, { useEffect } from "react";
import io from "socket.io-client"

const Dashboard = () => {
  const { NEXT_PUBLIC_SOCKET_URL } = process.env;
  const socket = io(NEXT_PUBLIC_SOCKET_URL);

  useEffect(() => {
    socket.on('connect', (socket) => {
      // socket.data = "alice";
      console.log('[SOCKET] Socket is conected.');
      socket.emit()
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